#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


void  print_solution(int *board, int n)
{
	int	i = 0;

	while (i < n)
	{
		fprintf(stdout, "%d", board[i]);
		if (i < n - 1)
			fprintf(stdout, " ");
		i++;
	}
	fprintf(stdout, "\n");
}

int	ft_abs(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

int	is_safe(int *board, int col, int row)
{
	int prev = 0;

	while (prev < col)
	{
		if (board[prev] == row)
			return (0);
		if (ft_abs(board[prev] - row) == col -prev)
			return (0);
		prev++;
	}
	return (1);
}

void  solve(int *board, int col, int n)
{
	int	row = 0;
	
	if (col == n)
	{
		print_solution(board, n);
		return ;
	}
	while (row < n)
	{
		if (is_safe(board, col, row))
		{
			board[col] = row;
			solve(board, col + 1, n);
		}
		row++;
	}
}


int	main(int argc, char **argv)
{
	if (argc != 2 || !argv[1][0])
		return (1);
	int	n = atoi(argv[1]);
	if (n <= 0)
		return (1);
	int	*board = malloc(sizeof(int) * n);
	if (!board)
		return (1);
	solve(board, 0, n);
	free(board);
	return (0);

}
