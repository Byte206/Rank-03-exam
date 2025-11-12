#include <unistd.h>
#include <stdio.h>
#include <string.h>

int	ft_strlen(char *str)
{
	int i = 0;
	while (str[i])
		i++;
	return (i);
}

void  ft_putstr(char *str)
{
	if (!str)
		return ;
	int i = 0;
	while (str[i])
	{
		write (1, &str[i], 1);
		i++;
	}
}

void  ft_swap(char *a, char *b)
{
	char tmp = *a;
	*a = *b;
	*b = tmp;
	return ;
}

void  ft_sort(char *str, int len)
{
	int i = 0;
	char  tmp;

	while (i < len - 1)
	{
		if (str[i] > str[i + 1])
		{
			ft_swap(&str[i], &str[i + 1]);
			i = 0;
		}
		else {
			i++;
		}
	}
}

int	ft_next_permutation(char *str, int len)
{
	int i = len - 2;
	while (i <= 0 && str[i] >= str[i + 1])
		i--;
	if (i < 0)
		return (0);
	return (0);
}

int main(int argc, char **argv)
{
	if (argc != 2)
		return (1);
	char *str = argv[1];
	int len = ft_strlen(str);
	ft_sort(str, len);
	ft_putstr(str);
	while (ft_next_permutation(str, len))
		ft_putstr(str);
	return (0);
}
