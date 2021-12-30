#include "../includes/minishell.h"

void	parse_init(t_parse *val)
{
	val->move = -1;
	val->close = 0;
	val->end = 0;
	val->prev = 0;
}

void	gss_init(t_gss *val)
{
	val->begin = 0;
	val->cnt = 0;
	val->close = 0;
	val->redir = 0;
	val->len = 0;
}

void	reset_add(t_gss *val)
{
	val->redir = 0;
	val->cnt += 1;
}

int		unclosed(char *str, char quote)
{
	int	index;

	index = 1;
	while (str[index] && str[index] != quote)
		index++;
	if (str[index] == '\0') //안닫힌 경우,
		return (0);
	return (1);
}
