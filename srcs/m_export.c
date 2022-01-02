#include "../includes/minishell.h"

void    free_trash(char **arr)
{
    int i;

    i = 0;
    while (arr[++i] != NULL)
        free(arr[i]);
    free(arr);
}

void    enrol_env(t_minishell *mini, char *new_key, char *new_value)
{
    char        **temp;
    char        **temp2;
    int         i;

    temp = (char **)malloc(sizeof(char *) * (mini->len + 2));
    if (temp == NULL)
        exit_clean(mini, EXIT_FAILURE);
    temp2 = (char **)malloc(sizeof(char *) * (mini->len + 2));
    if (temp2 == NULL)
        exit_clean(mini, EXIT_FAILURE);
    i = -1;
    while (++i < mini->len)
    {
        temp[i] = mini->key[i];
        temp2[i] = mini->content[i];
    }
    temp[i] = new_key;
    temp2[i++] = new_value;
    temp[i] = NULL;
    temp2[i] = NULL;
    free(mini->key);
    free(mini->content);
    mini->key = temp;
    mini->content = temp2;
}

void    add_path(t_minishell *mini, char *str, char *chr)
{
    char        *key;
	char        *value;
    char        **arr;

    if (key_check_str(str, '=') == FAIL)
    {
        alert_export_error("export", str);
        return ;
    }
    arr = ft_split(str, '=');
    if (arr == NULL)
        exit_clean(mini, EXIT_FAILURE);
    key = arr[0];
    free_trash(arr);
    value = ft_strdup(chr + 1);
    if (value == NULL)
        exit_clean(mini, EXIT_FAILURE);
    enrol_env(mini, key, value);
    mini->len += 1;
}

int mini_export(t_minishell *mini, int fd_out)
{
	int			i;
    char        *chr;

    g_exit = 0;
	i = 0;
	while(mini->lo->cmdline[++i].cmd && mini->lo->cmdline[i].redir_flag == 0)
	{
        if ((key_check_char(mini->lo->cmdline[i].cmd[0])) == FAIL)
        {
            alert_export_error("export", mini->lo->cmdline[i].cmd);
            continue;
        }
        chr = ft_strchr(&mini->lo->cmdline[i].cmd[1], '=');
        if (chr == NULL)
            continue;
        add_path(mini, mini->lo->cmdline[i].cmd, chr);
	}
	if ((mini->lo->cmdline[1].cmd) == NULL)
		show_declare_x(mini, fd_out);
    else if ((mini->lo->cmdline[1].redir_flag) == 1)
        show_declare_x(mini, fd_out);
	return (0);
}
