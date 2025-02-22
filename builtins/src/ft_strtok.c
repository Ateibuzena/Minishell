#include "../minishell/minishellft.h"

// Función auxiliar para verificar si un carácter es un delimitador
static int ft_is_delimiter(char c, const char *delimiter)
{
    while (*delimiter)
    {
        if (c == *delimiter)
        {
            return (1);  // Si encontramos el delimitador, devolvemos 1
        }
        delimiter++;
    }
    return (0);  // Si no encontramos el delimitador, devolvemos 0
}

char *ft_strtok(char *str, const char *delim)
{
    static char *next_token;
    char *token_start;

    if (!next_token)
        next_token = NULL;
    token_start = NULL;
    if (str == NULL && next_token == NULL) 
        return (NULL);

    if (str != NULL)
        next_token = str;

    // Si hemos llegado al final de la cadena
    if (next_token == NULL || *next_token == '\0')
        return (NULL);

    // Saltar los delimitadores iniciales
    while (*next_token && ft_is_delimiter(*next_token, delim))
        next_token++;

    // Si llegamos al final de la cadena
    if (*next_token == '\0')
	{
        next_token = NULL;
        return (NULL);
    }

    // Almacenar el comienzo del token
    token_start = next_token;

    // Avanzar hasta encontrar el siguiente delimitador
    while (*next_token && !ft_is_delimiter(*next_token, delim))
        next_token++;  // Avanzamos hasta el siguiente delimitador

    // Si encontramos un delimitador, lo reemplazamos con '\0' para terminar el token
    if (*next_token != '\0')
	{
        *next_token = '\0';
        next_token++;  // Avanzamos después del delimitador para el siguiente token
    }

    return (token_start);  // Devolvemos el token encontrado
}
