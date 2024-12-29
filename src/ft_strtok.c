#include "../minishellft.h"

// Función auxiliar para verificar si un carácter es un delimitador
static int ft_is_delimiter(char c, const char *delim)
{
    while (*delim) {
        if (c == *delim) {
            return 1;  // Si encontramos el delimitador, devolvemos 1
        }
        delim++;
    }
    return 0;  // Si no encontramos el delimitador, devolvemos 0
}

char *ft_strtok(char *str, const char *delim)
{
    static char *next_token = NULL;  // Puntero estático para almacenar el siguiente token

    if (str == NULL && next_token == NULL)
	{
        return (NULL);  // Si no hay más tokens, devolvemos NULL
    }

    if (str != NULL)
	{
        next_token = str;  // Iniciamos o reiniciamos el puntero para el primer token
    }

    // Si hemos llegado al final de la cadena
    if (next_token == NULL || *next_token == '\0')
	{
        return (NULL);
    }

    // Saltar los delimitadores iniciales
    while (*next_token && ft_is_delimiter(*next_token, delim))
	{
        next_token++;  // Avanzamos hasta el primer carácter que no sea delimitador
    }

    // Si llegamos al final de la cadena
    if (*next_token == '\0')
	{
        next_token = NULL;
        return (NULL);
    }

    // Almacenar el comienzo del token
    char *token_start = next_token;

    // Avanzar hasta encontrar el siguiente delimitador
    while (*next_token && !ft_is_delimiter(*next_token, delim))
	{
        next_token++;  // Avanzamos hasta el siguiente delimitador
    }

    // Si encontramos un delimitador, lo reemplazamos con '\0' para terminar el token
    if (*next_token != '\0')
	{
        *next_token = '\0';
        next_token++;  // Avanzamos después del delimitador para el siguiente token
    }

    return (token_start);  // Devolvemos el token encontrado
}
