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
	t_linked_order		*next;
	int			i;
	
	tmp = order;
	while(tmp)
	{
		next = tmp->next;
		i = 0;
		while (tmp->cmdline[i].cmd != NULL)
			free(tmp->cmdline[i++].cmd);
		free(tmp->cmdline);
		free(tmp->err_manage.errtoken);
		free(tmp);
		tmp = next;
	}
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