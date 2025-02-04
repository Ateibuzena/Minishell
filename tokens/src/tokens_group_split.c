#include "../tokensft.h"

// Función principal que procesa el comando completo
char **ft_split_command(const char *input)
{
    size_t capacity;
    char **result;
    const char *start = input;
    const char *current = input;
    size_t i;

    capacity = INITIAL_CAPACITY;
    result = malloc(capacity * sizeof(char *));
    if (!result)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    i = 0;
    while (*current)
    {
        if (*current == ' ' || *current == '<' || *current == '>' || *current == '|')
        {
            if (current > start)
                result[i++] = ft_process_token(start, current);
            i = ft_handle_delimiter(&current, result, i);
            start = current + 1;
        }
        if (i >= capacity)
            result = ft_resize_result(result, &capacity);
        current++;
    }

    if (current > start)
        result[i++] = ft_process_token(start, current);
    if (i >= capacity)
        result = ft_resize_result(result, &capacity);
    result[i] = NULL;
    return (result);
}

char **ft_group_tokens(char *entry)
{
    char **input;
    char **result;
    size_t i, j;
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
        if (ft_is_redirect(input[i]))
            result[j] = ft_process_redirect(input, &i);  // Procesar redirección
        else if (ft_strcmp(input[i], "|") != 0)
            result[j] = ft_process_pipe(input, &i);  // Mantener pipes intactos
        else
            result[j] = ft_process_command(input, &i);  // Agrupar comandos y argumentos
        j++;
    }
    result[j] = NULL; // Finalizar el array con NULL
    ft_freedouble(input);
    return (result);
}
