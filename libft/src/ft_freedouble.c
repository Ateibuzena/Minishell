#include "../libft.h"

void	ft_freedouble(char **ptr)
{
	int	i;

	i = 0;
	if (ptr[i])
	{
		while (ptr[i])
		{
			ptr[i] = NULL;
			free(ptr[i]);
			i++;
		}
		ptr = NULL;
		free(ptr);

	}
}

void	ft_freedouble_array(int **pipes, int len)
{
	int		j;

	j = 0;
	while (j < len)  // Solo liberamos lo que ya fue asignado
	{
		free(pipes[j]);
		j++;
	}
	free(pipes);
}