#include "../includes/minishell.h"

int		env_value_size(char *str, int size, t_minishell *mini)
{
	int index;
    char *key;

    key = ft_substr(str, 1, size);
	index = -1;
	while (mini->key[++index])
	{
		if (!ft_strcmp(key, mini->key[index]))
			return (ft_strlen(mini->content[index])); //key=value에서 value의 길이를 반환.
	}
	return (0); //일치하는 key가 없으면 0을 반환.
}

int		env_key_size(char *str)
{
	int index;

	index = 0;
	if (ft_isdigit(str[1])) // 변수명의 첫자리에 숫자가 오는 경우.
		return (1);
	while (str[++index])
	{
		if (!(ft_isalnum(str[index]) || str[index] == '_'))   // 변수명은 영문, '_' , 숫자가 올 수 있음.
			return (index - 1);
	}
	return (index - 1); // str[index] == key를 넘어선 값.
}

int		env_cnt(char *str, int *size, t_minishell *mini)
{
	int key_len;
	char *status;

	key_len = 0;
	if (str[1] == '?')
	{
		status = ft_itoa(g_exit);
		*size += ft_strlen(status);
		free(status);
		return (1);
	}
	if (str[1] == '\0' || str[1] == '\"') //ex) echo $"123"
	{
		*size += 1;
		return (0);
	}
	key_len = env_key_size(str); //env_key_size는 key값의 길이만 반환합니다. 인덱스는 $까지 포함해서 1을 더합니다.
	*size += env_value_size(str, key_len, mini);
	return (key_len);
}