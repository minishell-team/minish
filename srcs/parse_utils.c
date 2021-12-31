#include "../includes/minishell.h"

void	parse_init(t_parse *val, t_minishell *mini)
{
	val->move = -1;
	val->close = 0;
	val->end = 0;
	val->prev = 0;
	mini->lo = NULL;
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

int	unclosed(char *str, char quote)
{
	int	index;

	index = 1;
	while (str[index] && str[index] != quote)
		index++;
	if (str[index] == '\0')
		return (0);
	return (1);
}

int	ft_strcmp(const char *a, const char *b)
{
	while (*a || *b)
	{
		if (*a != *b)
			return (*a - *b);
		a++;
		b++;
	}
	return (*a - *b);
}

void	free_key_value(t_minishell *mini)
{
	int i;

	i = 0;
	while(mini->key[i])
	{
		free(mini->key[i]);
		free(mini->content[i]);
		i++;
	}
}