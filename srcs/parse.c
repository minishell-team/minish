#include "../includes/minishell.h"

static void	gss_init(t_gss *val)
{
	val->begin = 0;
	val->cnt = 0;
	val->close = 0;
	val->redir = 0;
	val->len = 0;
}

static void	reset_add(t_gss *val)
{
	val->redir = 0;
	val->cnt += 1;
}

void	get_split_size2(const char *s, const char c, t_gss *val)
{
	// ex) cat[_]
	if (*s == c && val->close == 0)
	{
		reset_add(val);
		val->begin = 0;
	}
	// ex) cat toast> or cat toast>>
	else if ((*s == '<' || *s == '>') && val->close == 0)
	{
		if (val->redir == 0 && *(s - 1) != ' ')
			val->cnt++;
		val->redir++;
	}
	// ex) echo temp>[?]
	else if (*s != c && *s != '\'' && !(*s == '>' || *s == '<') \
		&& val->close == 0 && (*(s - 1) == '>' || *(s - 1) == '<'))
		reset_add(val);
	// ex) 'echo temp>'
	else if (*s == '\'' && val->close == '\'' \
		&& (*(s - 1) == '>' || *(s - 1) == '<'))
		reset_add(val);
	// ex) "echo temp>"
	else if (*s == '"' && val->close == '"' \
		&& (*(s - 1) == '>' || *(s - 1) == '<'))
		reset_add(val);
}

int	get_split_size(const char *s, const char c)
{
	t_gss	val;

	gss_init(&val);
	while (*s)
	{
		if (*s == '"' && val.close == 0)
			val.close = '"';
		else if (*s == '"' && val.close == '"')
			val.close = 0;
		else if (*s == '\'' && val.close == 0)
			val.close = '\'';
		else if (*s == '\'' && val.close == '\'')
			val.close = '0';
		if (val.begin == 0)
		{
			if (*s != c)
				val.begin = 1;
			if (*s == '<' || *s == '>')
				val.redir++;
		}
		else
			get_split_size2(s, c, &val);
		s++;
	}
	return (val.cnt + val.begin);
}

static void	split_fail_free(t_token *res, int i)
{
	int	move;

	move = 0;
	while (move < i)
	{
		free(res[move].cmd);
		move++;
	}
	free(res);
	return ;
}

static void	cal_len2(const char *s, const char c, t_gss *val)
{
	while (s[val->len])
	{
		if (s[val->len] == '"' && val->close == '"')
			val->close = 0;
		else if (s[val->len] == '"' && val->close == 0)
			val->close = '"';
		else if (*s == '\'' && val->close == 0)
			val->close = '\'';
		else if (*s == '\'' && val->close == '\'')
			val->close = '0';
		if (val->begin == 0 && s[val->len] != c)
		{
			val->begin = 1;
			val->len++;
		}
		else
		{
			if (s[val->len] == c && val->close == 0)
				break ;
			else if ((s[val->len] == '>' || s[val->len] == '<') \
				&& val->close == 0)
				break ;
			else
				val->len++;
		}
	}
}

static int	cal_len(const char *s, const char c)
{
	t_gss	val;

	gss_init(&val);
	if (s[val.len] == '>' || s[val.len] == '<')
	{
		while (s[val.len])
		{
			if (s[val.len] == '>' || s[val.len] == '<')
				val.len++;
			else
				return (val.len);
		}
	}
	cal_len2(s, c, &val);
	return (val.len);
}

char *cmd_dup(const char *line, char pivot, int *start)
{
	int len;
	int move;
	char *cmd;

	len = 0;
	// 함수처리
	len = cal_len(&line[*start], pivot);
	cmd = (char *)malloc(sizeof(char) * (len + 1));
	if (!cmd)
		return (0);
	move = -1;
	while (++move < len)
		cmd[move] = line[*start + move];
	cmd[move] = '\0';
	*start += len;
	return (cmd);
}

t_token *cmd_split(const char *line, const char pivot, int move)
{
	t_token	*res;
	int		token_i;

	token_i = -1;
	if (!line)
		return (0);
	res = (t_token *)malloc(sizeof(t_token) \
		* (get_split_size(line, pivot) + 1));
	if (!res)
		return (0);
	printf("str: [%s]\n", line);
	while (line[move])
	{
		if (line[move] == pivot)
			move++;
		else
		{
			res[++token_i].cmd = cmd_dup(line, pivot, &move);
			if (!res->cmd)
			{
				split_fail_free(res, token_i);
				return (0);
			}
			res[token_i].redir_flag = 0;
		}
	}
	res[++token_i].cmd = NULL;
	return (res);
}

t_linked_order	*create_node(char *line)
{
	t_linked_order	*node;

	node = (t_linked_order *)malloc(sizeof(t_linked_order));
	node->next = NULL;
	if (!node)
		return (0);
	node->cmdline = cmd_split(line, ' ', 0);
	// div token
	return (node);
}

int	insert_LS(t_minishell *mini, char *line)
{
	t_linked_order	*list;
	t_linked_order	*node;

	list = mini->lo;
	node = create_node(line);
	if (!node)
		return (0);
	if (!list)
		mini->lo = node;
	else
	{
		while (list->next)
			list = list->next;
		list->next = node;
	}
	return (1);
}

void	parse_init(t_parse *val)
{
	val->move = -1;
	val->close = 0;
	val->end = 0;
	val->prev = 0;
}

void	parse(t_minishell *mini, char *line)
{
	t_parse val;
	
	parse_init(&val);
	while (++val.move >= 0)
	{
		if ((line[val.move] == '\'' || line[val.move] == '\"') && val.close == 0)
			val.close = 1;
		else if ((line[val.move] == '\'' || line[val.move] == '\"') && val.close == 1)
			val.close = 0;
		if ((line[val.move] == '|' && val.close == 0) || line[val.move] == '\0')
		{
			if (line[val.move] == '\0')
				val.end = 1;
			if (line[val.move] == '|')
				line[val.move] = '\0';
			if (!insert_LS(mini, &line[val.prev]))
			{
				//free_all_list(mini);
				return;
			}
			if (val.end)
				break;
			val.prev = val.move + 1;
		}
	}
}
/*
int main(void)
{
	t_minishell *mini;
	t_linked_order *list;
	t_token *token;
	int i;
	char srr[500] = "echo abc>>123 | grep > 123 | 'greap>123'";

	mini = (t_minishell *)malloc(sizeof(t_minishell));
	mini->lo = NULL;
	parse(mini, srr);
	list = mini->lo;
	i = 1;
	printf("==============\n");
	while (list)
	{
		token = list->cmdline;
		printf("list %d: \n", i++);
		while (token->cmd)
		{
			printf("%s\n", token->cmd);
			token++;
		}
		list = list->next;
	}
}
*/