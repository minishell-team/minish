#include "libft.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	n;
	int	count_minus;

	i = 0;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\r'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == ' ')
		i++;
	count_minus = 0;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			count_minus = 1;
		i++;
	}
	n = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		n = n * 10 + str[i] - '0';
		i++;
	}
	if (count_minus > 0)
		n = n * (-1);
	return (n);
}
