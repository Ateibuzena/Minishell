
#include <ctype.h>

#define MAX_TOKENS 100

#include "../tokensft.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TOKENS 100

// Función para manejar los tokens normales (comandos y sus argumentos)
char *ft_process_token(const char *start, const char *current) {
    size_t length = current - start;
    char *token = malloc(length + 1);
    if (!token) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    ft_strncpy(token, start, length);
    token[length] = '\0';
    return token;
}

// Función para manejar los delimitadores como <, >, |
char *ft_process_delimiter(const char *current) {
    char *token = malloc(2);
    if (!token) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    token[0] = *current;
    token[1] = '\0';
    return token;
}

// Función para redimensionar el array de resultados
char **ft_resize_result(char **result, size_t *capacity) {
    *capacity *= 2;  // Doblamos la capacidad actual
    char **new_result = malloc(*capacity * sizeof(char *));
    if (!new_result) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    // Copiamos los elementos existentes al nuevo array
    for (size_t i = 0; i < *capacity / 2; i++) {
        new_result[i] = result[i];
    }

    // Liberamos el array anterior
    free(result);
    return new_result;
}

// Función principal que procesa el comando completo
char **ft_split_command(const char *input) {
    size_t capacity = INITIAL_CAPACITY;  // Capacidad inicial
    char **result = malloc(capacity * sizeof(char *));
    if (!result) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    size_t i = 0;
    const char *start = input;
    const char *current = input;

    while (*current)
    {
        // Si es un delimitador (espacio, <, >, |)
        if (*current == ' ' || *current == '<' || *current == '>' || *current == '|') {
            if (current > start)
                result[i++] = ft_process_token(start, current);  // Procesar el token normal
            // Si es un delimitador, procesarlo por separado
            if (*current != ' ')
                result[i++] = ft_process_delimiter(current);
            start = current + 1;  // Mover el inicio al siguiente carácter
        }

        // Si hemos llegado al límite de la capacidad, redimensionamos
        if (i >= capacity)
            result = ft_resize_result(result, &capacity);

        current++;  // Avanzar al siguiente carácter
    }

    // Procesar el último token si lo hay
    if (current > start)
        result[i++] = ft_process_token(start, current);

    // Si hemos llegado al límite de la capacidad, redimensionamos nuevamente
    if (i >= capacity)
        result = ft_resize_result(result, &capacity);

    result[i] = NULL;  // Finalizar el array de resultados
    return result;
}

char **ft_group_tokens(char *entry)
{
    char **input;
    char **result;
    size_t i;
    size_t j;
    size_t length;

    input = ft_split_command(entry);
    result = malloc(MAX_TOKENS * sizeof(char *));
    if (!result)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    
    i = 0;
    j = 0;
    while (input[i])
    {
        if (ft_strcmp(input[i], "<") != 0 || ft_strcmp(input[i], ">") != 0)
        {
            // Concatenar < o > con su archivo contiguo
            length = ft_strlen(input[i]) + ft_strlen(input[i + 1]) + 2;
            result[j] = malloc((length * sizeof(char)));
            if (!result[j])
            {
                perror("malloc");
                exit(EXIT_FAILURE);
            }
            ft_snprintf(result[j], length, input[i], input[i + 1]);
            i += 2; // Saltar el siguiente token ya que fue procesado
        }
        else if (ft_strcmp(input[i], "|") != 0)
        {
            // Mantener los pipes intactos
            result[j] = ft_strdup(input[i]);
            if (!result[j])
            {
                perror("strdup");
                exit(EXIT_FAILURE);
            }
            i++;
        }
        else
        {
            // Agrupar comandos con sus argumentos
            length = ft_strlen(input[i]) + 1;
            result[j] = malloc((length) * sizeof(char));
            if (!result[j])
            {
                perror("malloc");
                exit(EXIT_FAILURE);
            }
            ft_strcpy(result[j], input[i]);

            // Concatenar argumentos al comando
            while (input[i + 1] && ft_strcmp(input[i + 1], "|") == 0
                    && ft_strcmp(input[i + 1], "<") == 0
                    && ft_strcmp(input[i + 1], ">") == 0)
            {
                length += ft_strlen(input[i + 1]) + 1;
                result[j] = realloc(result[j], length); //no puedo usar realloc, o implementar ft_realloc
                if (!result[j])
                {
                    perror("realloc");
                    exit(EXIT_FAILURE);
                }
                ft_strcat(result[j], " ");
                ft_strcat(result[j], input[i + 1]);
                i++;
            }
            i++; // Avanzar al siguiente token
        }
        j++;
    }

    result[j] = NULL; // Terminar el array con NULL
    ft_freedouble(input);
    return result;
}

void ft_remove_pipes(char **result)
{
    size_t i;
    size_t j;

    i = 0;
    j = 0;
    while (result[i])
    {
        // Si el token es un pipe, lo omitimos
        if (ft_strcmp(result[i], "|") == 0)
        {
            result[j] = result[i]; // Mover el token a la nueva posición
            j++;
        }
        i++;
    }
    result[j] = NULL; // Terminar el array con NULL
}