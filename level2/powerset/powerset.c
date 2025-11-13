#include <stdio.h>
#include <stdlib.h>

void  print_subset(int *arr, int *path,int len)
{
	int i = -1;
	int first = 1;

	while (++i < len)
	{
		if (path[i])
		{
			if (!first)
				printf(" ");
			printf("%d", arr[i]);
			first = 0;
		}
	}
	printf("\n");
}

void  backtrack(int *arr, int *path, int len, int idx, int sum, int target)
{
	if (idx == len)
	{
		if (sum == target)
			print_subset(arr, path, len);
		return ;
	}
	path[idx] = 1;
	backtrack(arr, path, len, idx + 1, sum + arr[idx], target);
	path[idx] = 0;
	backtrack(arr, path, len, idx + 1, sum, target);
}


int main(int argc, char **argv)
{
	if (argc < 2)
		return (1);
	int i = -1;
	int target = atoi(argv[1]);
	int len = argc - 2;
	int *arr = malloc(sizeof(int) * len);
	int *path = calloc(len, sizeof(int));
	if (!arr || !path)
		return (1);
	while (++i < len)
		arr[i] = atoi(argv[i + 2]);
	backtrack(arr, path, len, 0, 0, target);
	free(arr);
	free(path);
	return (0);
}
