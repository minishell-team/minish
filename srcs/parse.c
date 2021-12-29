#include "../includes/minishell.h"

t_linked_order *create_node(char *line)
{
	t_linked_order *node;

	node = (t_linked_order *)malloc(sizeof(t_linked_order));
	node->next = NULL;
	if(!node)
		return (0);
	// div token
	return (node);
}

int	insert_LS(t_minishell *mini, char *line)
{
	t_linked_order *list;
	t_linked_order *node;

	list = mini->lo;
	node = create_node(line);
	if(!node)
		return (0);
	if(!list)
		mini->lo = node;
	else
	{
		while(list->next)
			list = list->next;
		list->next = node;
	}
	return (1);
}

void	free_list(t_minishell *mini)
{
	t_linked_order *l;
	t_linked_order *next;

	l = mini->lo;
	while(l)
	{
		next = l->next;
		free(l);
		l = next;
	}
}

void	parse(t_minishell *mini, char *line)
{
	t_linked_order *l;
	int	move;
	int prev;

	l = mini->lo;
	move = 0;
	prev = 0;
	while(line[move])
	{
		if (line[move] == '|')
		{
			line[move] = '\0';
			if(!insert_LS(mini, line))
			{
				free_all_list(mini);
				return ;
			}
			prev = move + 1;
		}
		move++;
	}
}
