#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>


#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif


void  ft_filtrer(char *str, char *filter)
{
	int i = 0;
	int	j = 0;
	int	len = strlen(filter);

	while (str[i])
	{
		j = 0;
		while (str[j + i] && str[j + i] == filter[j])
			j++;
		//printf("j:%d len:%d\n", j, len);
		if (j == len)
		{
			int k = 0;
			while (k < len)
			{
				write (1, "*", 1);
				k++;
			}
			i += j;
		}
		else {
			write (1, &str[i], 1);
			i++;
		}
	}
}


int	main(int argc, char **argv)
{
	if (argc != 2 || !argv[1][0])
		return (1);
	char  str[999999];
	int	  bytes_read = 1;
	int	  i = 0;

	while (bytes_read > 0)
	{
		bytes_read = read(0, &str[i], BUFFER_SIZE);
		if (bytes_read < 0)
		{
			perror("Error");
			return (1);
		}
		i += bytes_read;
	}
	str[i] = '\0';
	ft_filtrer(str, argv[1]);
	return (0);
}
