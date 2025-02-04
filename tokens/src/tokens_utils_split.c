#include "../tokensft.h"

// Función para manejar delimitadores dobles como << o >>
char *ft_process_double_delimiter(const char *current)
{
    char *token = malloc(3);
    if (!token)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    token[0] = *current;
    token[1] = *(current + 1);
    token[2] = '\0';
    return (token);
}

// Función para manejar los tokens normales (comandos y sus argumentos)
char *ft_process_token(const char *start, const char *current)
{
    size_t length;
    char *token;
    
    length = current - start;
    token = malloc(length + 1);
    if (!token)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    ft_strncpy(token, start, length);
    token[length] = '\0';
    return (token);
}

// Función para manejar los delimitadores como <, >, |
char *ft_process_delimiter(const char *current)
{
    char *token;
    
    token = malloc(2);
    if (!token)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    token[0] = *current;
    token[1] = '\0';
    return (token);
}

// Función para redimensionar el array de resultados
char **ft_resize_result(char **result, size_t *capacity)
{
    char **new_result;
    size_t  i;

    (*capacity) *= 2;  // Doblamos la capacidad actual
    new_result = malloc((*capacity) * sizeof(char *));
    if (!new_result)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    i = 0;
    // Copiamos los elementos existentes al nuevo array
    while(i < *capacity / 2)
    {
        new_result[i] = result[i];
        i++;
    }
    // Liberamos el array anterior
    free(result);
    return (new_result);
}

// Función para manejar un delimitador detectado
size_t ft_handle_delimiter(const char **current, char **result, size_t i)
{
    if ((**current == '<' && *(*current + 1) == '<') || 
        (**current == '>' && *(*current + 1) == '>'))
    {
        result[i++] = ft_process_double_delimiter(*current);
        (*current)++; // Saltar el segundo carácter del delimitador
    }
    else if (**current != ' ')
        result[i++] = ft_process_delimiter(*current);

    return (i);
}
