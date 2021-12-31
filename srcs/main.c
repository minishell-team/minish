#include "../includes/minishell.h"

int	g_exit = 0;

void	signal_handler(int sig)
{
	pid_t	pid;
	int		status;

	pid = waitpid(-1, &status, WNOHANG);
	if (sig == SIGINT)
	{
		if (pid == -1)
		{
			rl_on_new_line();
			rl_redisplay();
			ft_putstr_fd("  \n", STDOUT);
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
		else
			ft_putstr_fd("\n", STDOUT);
	}
	else if(sig == SIGQUIT)
	{
		if (pid == -1)
		{
			rl_on_new_line();
			rl_redisplay();
			ft_putstr_fd("  \b\b", STDOUT);
		}
		else
			ft_putstr_fd("Quit: 3\n", STDOUT);
	}
}

void	len_env(t_minishell *mini)
{
	int	i;

	i = 0;
	while (mini->env[i])
		i++;
	mini->len = i;
}

void	init_struct_env(t_minishell *mini)
{
	mini->key = malloc(sizeof(char *) * (mini->len + 1));
	if (!mini->key)
		exit(EXIT_FAILURE);
	mini->content = malloc(sizeof(char *) * (mini->len + 1));
	if (!mini->content)
		exit(EXIT_FAILURE);
}

void	init_mini(t_minishell *mini, char **argv, char **envp)
{
	int		i;
	char	**env_aux;

	dup2(STDIN, STDIN_BACKUP); 
	dup2(STDOUT, STDOUT_BACKUP);
    signal(SIGINT, signal_handler);
	signal(SIGQUIT, signal_handler);
	mini->argv = argv;
	mini->env = envp;
	len_env(mini);
	init_struct_env(mini);
	i = -1;
	while (mini->env[++i])
	{
		env_aux = ft_split(mini->env[i], '=');
		mini->key[i] = ft_strdup(env_aux[0]);
		if (env_aux[1])
			mini->content[i] = ft_strdup(env_aux[1]);
		else
			mini->content[i] = ft_strdup("");
		free_char_array(env_aux);
		env_aux = NULL;
	}
	mini->key[i] = NULL;
	mini->content[i] = NULL;
}

int				main(int argc, char **argv, char **envp)
{
	char			*line;
	t_minishell		mini;
	t_linked_order	*order;

	init_mini(&mini, argv, envp);
	while (1)
	{
		line = readline("minishell$ ");
		if (line != NULL)
		{
			if (line[0] != '\0' && !chk_line(line))
			{
				add_history(line);
				parse(&mini, line);
				order = mini.lo;
				g_exit = exec(&mini);
				free_all_list(order);
			}
			free(line);
			continue;
		}
		ft_putendl_fd("\x1b[1A\033[12Cexit", STDOUT);
		break ;
	}
	return (0);
}
