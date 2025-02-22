#include "../builtinsft.h"

// Función para verificar si el argumento es un "-n" válido
static int	ft_n_flag(const char *arg)
{
	int	i;

	i = 1;
	if (arg[0] != '-')
		return (0);
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1); // Es un "-n" válido
}

static char	*ft_remove_quotes(const char *arg)
{
	char	*result;
	int		j;
	int		i;

	j = 0;
	i = 0;
	result = malloc((ft_strlen(arg) + 1) * sizeof(char));
	if (!result)
		return (perror("Error: Malloc failed"), NULL);
	while (arg[i])
	{
		if (arg[i] != '\'' && arg[i] != '"')
			result[j++] = arg[i];
		i++;
	}
	result[j] = '\0';
	return (result);
}

// Función para manejar el comando echo
int	ft_echo(char **args, t_Env *env)
{
    int		i;
    int		newline;
	char	*expanded;
	char	*cleaned;
	
	newline = 1;  // Suponer que agregaremos un salto de línea por defecto
	i = 1;
    // Comprobar si el primer argumento es -n
    while (args[i] && ft_n_flag(args[i]))
    {
        newline = 0;  // No imprimir salto de línea
        i++;  // Saltar el -n
    }

    // Imprimir los argumentos
    while (args[i])
    {
		expanded = ft_expand_variables(args[i], env);
		//falta parseo de comillas:
		cleaned = ft_remove_quotes(expanded);

        printf("%s", expanded);
		
		free(expanded);
		free(cleaned);
        
		if (args[i + 1])
            printf(" ");  // Agregar espacio entre palabras
        i++;
    }

    // Si no es la opción -n, imprimir salto de línea
    if (newline)
        printf("\n");

    return (1);
}