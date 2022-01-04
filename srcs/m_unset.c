#include "../includes/minishell.h"

void	make_new_space(t_minishell *mini, char ***temp, char ***temp2)
{
	*temp = (char **)malloc(sizeof(char *) * (mini->len));
	if (*temp == NULL)
		exit_clean(mini, EXIT_FAILURE);
	*temp2 = (char **)malloc(sizeof(char *) * (mini->len));
	if (*temp2 == NULL)
	{
		free(*temp);
		exit_clean(mini, EXIT_FAILURE);
	}
}

void	pop_env(t_minishell *mini, int key_index, char ***e_key, char ***e_val)
{
	char	**temp;
	char	**temp2;
	int		i;

	make_new_space(mini, &temp, &temp2);
	temp[mini->len] = NULL;
	temp2[mini->len] = NULL;
	i = -1;
	while ((*e_key)[++i])
	{
		if (i == key_index)
		{
			free((*e_key)[i]);
			free((*e_val)[i]);
			continue ;
		}
		temp[(i - (i >= key_index))] = (*e_key)[i];
		temp2[(i - (i >= key_index))] = (*e_val)[i];
	}
	free(*e_key);
	free(*e_val);
	*e_key = temp;
	*e_val = temp2;
}

void	remove_path(t_minishell *mini, char *key, char ***e_key, char ***e_val)
{
	int	key_index;

	key_index = find_env(mini, key);
	if (key_index == -1)
		return ;
	pop_env(mini, key_index, e_key, e_val);
	mini->len -= 1;
}

int	mini_unset(t_minishell *mini, char ***e_key, char ***e_val)
{
	int			i;

	g_exit = 0;
	i = 0;
	while (mini->lo->cmdline[++i].cmd && mini->lo->cmdline[i].redir_flag == 0)
	{
		if ((key_check_char(mini->lo->cmdline[i].cmd[0])) == FAIL)
			alert_export_error("unset", mini->lo->cmdline[i].cmd);
		else if (ft_strchr(&mini->lo->cmdline[i].cmd[1], '=') != NULL)
			alert_export_error("unset", mini->lo->cmdline[i].cmd);
		else if ((key_check_str(mini->lo->cmdline[i].cmd, '\0')) == FAIL)
			alert_export_error("unset", mini->lo->cmdline[i].cmd);
		else
			remove_path(mini, mini->lo->cmdline[i].cmd, e_key, e_val);
	}
	return (0);
}
