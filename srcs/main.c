#include "../includes/minishell.h"

int	g_exit = 0;

void	handle_signal(int signo)
{
	pid_t	pid;
	int		status;

	pid = waitpid(-1, &status, WNOHANG);
	// write(1,"asd\n",4);
	//-1 : 자식 프로세스를 기다림.
	//status : 자식 프로세스가 종료되면 자식 pid값이 할당 됨.
	//WNOHANG : 자식 프로세스가 종료되지 않아서 pid를 회수할 수 없는 경우 반환값으로 0을 받음.
	if (signo == SIGINT)
	{
		if (pid == -1)
		//pid == -1 : 자식 프로세스가 없는 경우
		{
		rl_on_new_line();//개행을 실행하기 위한 엔터 역할
		rl_redisplay();// 입력받은 것 다시 출력
		ft_putstr_fd("  \n",STDOUT);//개행
		rl_on_new_line();//개행을 실행하기 위한 엔터 역할
		// readline 다시 실행하는 코드
		rl_replace_line("", 0);//buffer초기화
		rl_redisplay();//실행
		}
		else
			ft_putstr_fd(" \n",STDOUT);//다시출력해서 커서가 글자의 끝에 있음.
	}
	else if(signo == SIGQUIT)
	{
		if (pid == -1) //ok.
		{
		rl_on_new_line();//입력 받은 것 종료
		rl_redisplay();// 입력받은 것 다시 출력
		ft_putstr_fd("  \b\b",STDOUT);
		}
		else
			ft_putstr_fd("Quit: 3\n",STDOUT);//다시출력해서 커서가 글자의 끝에 있음.
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

void	init_mini(t_minishell *mini, char **envp)
{
	int		i;
	char	**env_aux;

	dup2(STDIN, 420); 
	dup2(STDOUT, 421);
    signal(SIGINT, handle_signal);//ctrl + c
	signal(SIGQUIT, handle_signal);//ctrl + '\'
	mini->env = envp;
	len_env(mini);
	init_struct_env(mini);
	i = 0;
	while (mini->env[i])
	{
		env_aux = ft_split(mini->env[i], '=');
		mini->key[i] = ft_strdup(env_aux[0]);
		if (env_aux[1])
			mini->content[i] = ft_strdup(env_aux[1]);
		else
			mini->content[i] = ft_strdup("");
		free_char_array(env_aux);
		env_aux = NULL;
		i++;
	}
	mini->key[i] = NULL;
	mini->content[i] = NULL;
}

int				main(int argc, char **argv, char **envp)
{
	char				*line;
	char				**cpenv;
	t_minishell			mini;

	init_mini(&mini, envp);
	while (1)
	{
		line = readline("minishell$ ");
		if (line)
		{
			if (*line != '\0' && !chk_line(line))
			{
				add_history(line);
				parse(&mini.lo, line);
				g_exit = exec(&mini, argv);
				free_all_list(&mini.lo);
			}
			free(line); // readline으로 할당한 line을 해제시켜줍니다.
			continue;
		}
		write(1,"\x1b[1A\033[12Cexit\n",15);
		break ;
	}
	return (0);
}
