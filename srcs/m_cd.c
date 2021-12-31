#include "../includes/minishell.h"

int find_env(t_minishell *mini, char *key)
{
	int	i;
	int	len_key;

	i = -1;
	len_key = ft_strlen(key);
	while (mini->key[++i])
		if (ft_strncmp(mini->key[i], key, len_key + 1) == 0)
			return (i);
	return (-1);
}

int cd_error(t_minishell *mini)
{
    char *pst_buffer;

    pst_buffer = getcwd(0, 0);
    chdir(pst_buffer);
    free(pst_buffer);
    mini->lo->err_manage.errcode = 3;
    mini->lo->err_manage.errindex = 1;
    return (ERROR);
}

void    set_path_root(t_minishell *mini)
{
    char *temp;
    char *path;

    temp = mini->lo->cmdline[1].cmd;
    path = ft_strjoin(getenv("HOME"), &mini->lo->cmdline[1].cmd[1]);
    mini->lo->cmdline[1].cmd = path;
    free(temp);
}

int cd_to_home(void)
{
    chdir(getenv("HOME"));
    return (NEED_INIT);
}

int mini_cd(t_minishell *mini)
{	
	if ((mini->lo->cmdline[1].cmd) == NULL)
        return (cd_to_home);
    if ((mini->lo->cmdline[1].redir_flag) == 1)
        return (cd_to_home);
	if (mini->lo->cmdline[1].cmd[0] == '\0')
		return (NEED_INIT);
	
	if (mini->lo->cmdline[1].cmd[0] == '~')
	{
		if(mini->lo->cmdline[1].cmd[1] == '/')
            set_path_root(mini);
		else if(mini->lo->cmdline[1].cmd[1] == '\0')
            return (cd_to_home);
	}
	if (chdir(mini->lo->cmdline[1].cmd) == ERROR)
        return (cd_error(mini));
	return (NEED_INIT);
}