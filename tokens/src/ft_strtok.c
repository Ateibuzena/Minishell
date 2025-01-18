#include "../tokensft.h"

// Función auxiliar para verificar si un carácter es un delimitador
static int ft_is_delimiter(char c, const char *delim)
{
    while (*delim)
    {
        if (c == *delim)
            return (1); // Es un delimitador
        delim++;
    }
    return (0); // No es un delimitador
}

// Función principal para tokenizar
char *ft_strtok(char *str, const char *delim)
{
    static char *next_token; // Puntero estático para el siguiente token
    char *token_start;

    next_token = NULL;
    // Si se pasa una nueva cadena, reiniciamos el puntero estático
    if (str != NULL)
        next_token = str;

    // Si no hay más tokens, devolvemos NULL
    if (next_token == NULL)
        return (NULL);

    // Saltar los delimitadores iniciales
    while (*next_token && ft_is_delimiter(*next_token, delim))
        next_token++;

    // Si llegamos al final de la cadena después de los delimitadores, devolvemos NULL
    if (*next_token == '\0')
        return (NULL);

    // Almacenar el inicio del token
    token_start = next_token;

    // Avanzar hasta el final del token (es decir, hasta encontrar un delimitador)
    while (*next_token && !ft_is_delimiter(*next_token, delim))
        next_token++;

    // Si encontramos un delimitador, lo reemplazamos con '\0' y avanzamos el puntero
    if (*next_token)
    {
        *next_token = '\0';
        next_token++;
    }

    return (token_start); // Devolvemos el token
}
