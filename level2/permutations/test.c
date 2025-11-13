#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void  ft_putstr(char *str)
{
	int i = 0;
	while (str[i])
	{
		write (1, &str[i], 1);
		i++;
	}
	write (1, "\n", 1);
}

void  ft_swap(char *a, char *b)
{
	char tmp = *a;
	*a = *b;
	*b = tmp;
	return ;
}

int	ft_strlen(char *str)
{
	int i = 0;
	while (str[i])
		i++;
	return (i);
}

void  ft_sort(char *str)
{
	int i = 0;
	int len = ft_strlen(str);
	while (i < len - 1)
	{
		if (str[i] > str[i + 1])
		{
			ft_swap(&str[i], &str[i + 1]);
			i = 0;
		}
		else 
			i++;
	}
	return ;
}

int	next_permutation(char *str)
{
	int len = ft_strlen(str);

	// Empezamos desde el penúltimo carácter y vamos hacia atrás.
	// Buscamos el primer índice 'i' tal que str[i] < str[i + 1].
	// Esto marca el punto donde la secuencia deja de ser descendente.
	int i = len - 2;
	while (i >= 0 && str[i] >= str[i + 1])
		i--;

	// Si no encontramos tal índice (i == -1),
	// significa que todo el string está ordenado de mayor a menor
	// (ya es la última permutación posible).
	if (i == -1)
		return (0);

	// Ahora buscamos desde el final el primer elemento 'j'
	// que sea mayor que str[i].
	int j = len - 1;
	while (str[j] <= str[i])
		j--;

	// Intercambiamos str[i] y str[j],
	// para “subir” un paso en el orden lexicográfico.
	ft_swap(&str[i], &str[j]);

	// Finalmente, invertimos el tramo a la derecha de 'i'
	// (de i+1 hasta el final),
	// para dejar esa parte en el orden más pequeño posible.
	int start = i + 1;
	int end = len - 1;
	while (start < end)
		ft_swap(&str[start++], &str[end--]);

	// Devolvemos 1 indicando que hemos generado una nueva permutación.
	return (1);
}


int main(int argc, char **argv)
{
	if (argc != 2 || !argv[1][0])
		return (1);
	char *str = argv[1];
	ft_sort(str);
	ft_putstr(str);
	while (next_permutation(str))
		ft_putstr(str);
	return (0);

}
