#include "../includes/minishell.h"

void	free_char_array(char **array)
{
	int	i;

	i = 0;
	while (array[i] != NULL)
	{
		free(array[i]);
		array[i] = NULL;
		i++;
	}
	free(array);
}

void	free_all_list(t_linked_order *order)
{
	t_linked_order		*tmp;
	int			i;

	while (order->next != NULL)
	{
		i = 0;
		tmp = order;
		order = order->next;
		while (tmp->cmdline[i].cmd != NULL)
			free(tmp->cmdline[i++].cmd);
		free(tmp->cmdline);
		free(tmp->err_manage.errtoken);
		free(tmp);
	}
	i = 0;
	while (order->cmdline[i].cmd != NULL)
		free(order->cmdline[i++].cmd);
	free(order->cmdline);
	free(order->err_manage.errtoken);
	free(order);
}

int	chk_line(char *line)
{
	int		i;

	i = 0;
	while (line[i] != '\0')
	{
		if (line[i] != 32 && !(line[i] >= 9 && line[i] <= 13))
			return (0);
		i++;
	}
	return (1);
}