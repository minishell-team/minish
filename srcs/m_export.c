#include "../includes/minishell.h"

int	make_new_export_space(char ***temp, char ***temp2, char ***env_key)
{
	int	len;

	len = 0;
	while ((*env_key)[len] != NULL)
		len += 1;
	*temp = (char **)malloc(sizeof(char *) * (len + 2));
	if (*temp == NULL)
		return (ERROR);
	*temp2 = (char **)malloc(sizeof(char *) * (len + 2));
	if (*temp2 == NULL)
	{
		free(*temp);
		return (ERROR);
	}
	return (SUCCESS);
}

int	enrol_env(char *new_key, char *new_value, char ***env_key, char ***env_val)
{
	char	**temp;
	char	**temp2;
	int		i;

	if (make_new_export_space(&temp, &temp2, env_key) == ERROR)
		return (ERROR);
	i = -1;
	while ((*env_key)[++i])
	{
		temp[i] = (*env_key)[i];
		temp2[i] = (*env_val)[i];
	}
	temp[i] = new_key;
	temp2[i++] = new_value;
	temp[i] = NULL;
	temp2[i] = NULL;
	free(*env_key);
	free(*env_val);
	*env_key = temp;
	*env_val = temp2;
	return (SUCCESS);
}

int	add_path(t_minishell *mini, char *str, char ***e_key, char ***e_val)
{
	char	*key;
	char	*value;
	char	**arr;
	char	*chr;

	chr = ft_strchr(&str[1], '=');
	if (chr == NULL)
		return (FAIL);
	if (key_check_str(str, '=') == FAIL)
		return (alert_export_error("export", str));
	arr = ft_split(str, '=');
	if (arr == NULL)
		exit_clean(mini, EXIT_FAILURE);
	key = arr[0];
	free_trash(arr);
	value = ft_strdup(chr + 1);
	if (value == NULL)
		exit_clean(mini, EXIT_FAILURE);
	if (check_unique_key(mini, key, value) == FAIL)
		return (FAIL);
	if (enrol_env(key, value, e_key, e_val) == ERROR)
		exit_clean(mini, EXIT_FAILURE);
	mini->len += 1;
	return (SUCCESS);
}

int	mini_export(t_minishell *mini, int fd_out, char ***e_key, char ***e_val)
{
	int		i;

	g_exit = 0;
	i = 0;
	while (mini->lo->cmdline[++i].cmd && mini->lo->cmdline[i].redir_flag == 0)
	{
		if ((key_check_char(mini->lo->cmdline[i].cmd[0])) == FAIL)
		{
			alert_export_error("export", mini->lo->cmdline[i].cmd);
			continue ;
		}
		add_path(mini, mini->lo->cmdline[i].cmd, e_key, e_val);
	}
	if ((mini->lo->cmdline[1].cmd) == NULL)
		show_declare_x(mini, fd_out);
	else if ((mini->lo->cmdline[1].redir_flag) == 1)
		show_declare_x(mini, fd_out);
	return (0);
}
