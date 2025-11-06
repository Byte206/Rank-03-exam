//Tenemos 3 strings,uno estatico para guardar lo que sobra cada llamada
//Verificamos Si nos han pasado un archivo y si buffer_size es valido
//reservamos memoria para buffer con malloc y buffer_size + 1
//Llamamos a funcion para poner la linea en *linea
//liberamos buffer
//Si linea esta vacio el static = Null Y retornamos nullo
//igualamos el static a la funcion set_line(line) en la que limitamos la linea hasta encontrar
//el salto de linea y creamos una nueva apartid de lo que sobre
//devolvemnos linea
/*
 * Funcion para llenar el buffer:
 *	variable para el valor de read
 *	String temporal
 *
 *	mientras read devuelva mas que 0
 *	  llamamos a read,escribimos en buffer y leemos buffer_size caracteres
 *	  si read da -1
 *	  free(static) y devolvemos nullo
 *	  
 *	  si read da = 0
 *		break del bucle
 *	  Terminamos buffer con nulo en la posicion que devuelve read
 *	  
 *	  Si es la primera iteracion de la funcion,la string static esta vacia asique la creamos
 *	  con ft_strdup("");
 *	  igualamos tmp a la static
 *	  static = ft_strjoin(tmp, buffer)
 *	  free(tmp)
 *	  Si encontranmos \n en la static break del bucle
 *	
 *	devolvemos static
 */


/*
*Funcion para set_line

	Iteramos string hasta llegar al final o un salto de linea
	Si al salir del bucle estamos en nullo,devolvemos nullo
	Sino,creamos una nueva string llamando a ft_substr,pasando la linea que recibe la funcion
	,la posicion de i + 1, y ft_strlen(line) - i + 1;
	si la nueva string esta vacia hacemos free de line y devolvemos nullo

	terminamos line con un nullo en i + 1;
	devolvemos nueva string
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif



int	ft_strlen(char *str)
{
	int i = 0;

	while (str[i])
		i++;
	return (i);
}

char  *ft_strdup(char *str)
{
	if (!str)
		return (NULL);
	char  *new = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (!new)
		return (NULL);
	int i = 0;
	while (str[i])
	{
		new[i] = '\0';
		i++;
	}
	new[i] = '\0';
	return (new);
}

int	ft_strchr(char *str, char c)
{
	int i = 0;

	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char  *ft_strjoin(char *s1, char *s2)
{
	if (!s1 || !s2)
		return (NULL);
	char  *new = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!new)
		return (NULL);
	int	i = 0;int j = 0;

	while (s1[i])
	{
		new[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		new[i + j] = s2[j];
		j++;
	}
	new[i + j] = '\0';
	return (new);
}

char  *ft_substr(char *str, int start, int size)
{
	int	len;
	int	i;
	char  *new;

	if (!str)
		return (NULL);
	len = ft_strlen(str);
	if (start >= len)
		return (ft_strdup(""));
	if (size > len - start)
		size = len - start;
	new = malloc(sizeof(char) * (size + 1));
	if (!new)
		return (NULL);
	i = 0;
	while (i < size && str[start + i])
	{
		new[i] = str[start + i];
		i++;
	}
	new[i] = '\0';
	return (new);
}



char  *fill_buffer(int fd, char *buffer, char *left)
{
	int bytes_read = 1;
	char *tmp;

	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read == 0)
			break;
		if (bytes_read == -1)
		{
			free(left);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		if (!left)
			left = ft_strdup("");
		tmp = left;
		left = ft_strjoin(tmp, buffer);
		free(tmp);
		if (!left)
		{
			return (NULL);
		}
		if (ft_strchr(left, '\n'))
			break;
	}
	return (left);
}


char  *set_line(char *line)
{
	int i = 0;
	char  *new;

	while (line[i] && line[i] != '\n')
		i++;
	if (line[i] == '\0')
		return (NULL);
	new = ft_substr(line, i + 1, (ft_strlen(line) - i + 1));
	if (!new)
	{
		free(line);
		return (NULL);
	}
	line[i + 1] = '\0';
	return (new);
}

char  *get_next_line(int fd)
{
	static char *left;
	char		*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buffer)
		return (NULL);
	line = fill_buffer(fd, buffer, left);
	free(buffer);
	if (!line || *line == '\0')
	{
		free(left);
		left = NULL;
		return (NULL);
	}
	left = set_line(line);
	return (line);
}


int main()
{
	int	fd = open("file.txt", O_RDONLY);
	char *line = get_next_line(fd);
	
	while (line)
	{
		printf("%s", line);
		line = get_next_line(fd);
	}
	close (fd);
}
