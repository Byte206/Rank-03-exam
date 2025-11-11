
//Definimos BUFFER_SIZE
/*creamos array reservando 999.999
 *si argc es != 2 o argv[1][0] esta vacio retornamos 1
 mientras bytes_read > 0 llamamos a read(0, line[i], BUFFER_SIZE) escribiiendo en line con el 
 index i y con buffer size, i += bytes_read
 al salir del bucle llamamos a funcion que filtra
 en la funcion que litra simplimente recorremos el string
 si encontramos la palabra a filtrar en el string imprimimos asteriscos,sino el string
 *
 *
 *
 *
 *
 *
*/




#include <stdio.h>
#include <unistd.h>
#include <string.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif





void  ft_filtrer(char *str, char *filtrer)
{
	int	len = strlen(filtrer);
	int	i = 0;
	int j = 0;

	while (str[i])
	{
		j = 0;
		while (str[i + j] == filtrer[j])
			j++;
		if (len == j)
		{
			j = 0;
			while (j <= len)
			{
				write (1, "*", 1);
				j++;
			}
			i += len;
		}
		write (1, &str[i], 1);
		i++;
	}
}


int main(int argc, char **argv)
{
	if (argc != 2 || !argv[1][0])
		return 1;
	int	bytes_read = 1;
	char  str[999999];
	int	i = 0;

	while (bytes_read > 0)
	{
		bytes_read = read(0, &str[i], BUFFER_SIZE);
		if (bytes_read == 0)
			break;
		if (bytes_read < 1)
		{
			return (1);
		}
		printf("bytes leidos:%d\n", bytes_read);
		i += bytes_read;
	}
	printf("Resultado:\n");
	ft_filtrer(str, argv[1]);
}


