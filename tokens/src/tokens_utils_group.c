#include "../tokensft.h"

int ft_is_redirect(const char *token)
{
    if (ft_strcmp(token, "<") != 0 || ft_strcmp(token, ">") != 0 ||
            ft_strcmp(token, "<<") != 0 || ft_strcmp(token, ">>") != 0)
        return (1);
    return (0);
}

char *ft_process_redirect(char **input, size_t *i)
{
    size_t length;
    char *result;
    
    // Concatenar redirección con su archivo contiguo
    length = ft_strlen(input[(*i)]) + ft_strlen(input[(*i) + 1]) + 2;
    result = malloc(length * sizeof(char));
    if (!result)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    ft_snprintf(result, length, input[(*i)], input[(*i) + 1]);
    (*i) += 2; // Saltar el siguiente token ya que fue procesado
    return (result);
}

char *ft_process_pipe(char **input, size_t *i)
{
    char *pipe_token;

    pipe_token = ft_strdup(input[(*i)]);
    if (!pipe_token)
    {
        perror("strdup");
        exit(EXIT_FAILURE);
    }
    ((*i))++;
    return (pipe_token);
}

char *ft_process_command(char **input, size_t *i)
{
    size_t length;
    char *command;

    length = ft_strlen(input[(*i)]) + 1;
    command = malloc(length * sizeof(char));
    if (!command)
    {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    ft_strcpy(command, input[(*i)]);

    // Concatenar los argumentos al comando
    while (input[(*i) + 1] && ft_strcmp(input[(*i) + 1], "|") == 0
            && ft_strcmp(input[(*i) + 1], "<") == 0
            && ft_strcmp(input[(*i) + 1], ">") == 0
            && ft_strcmp(input[(*i) + 1], ">>") == 0)
    {
        length += ft_strlen(input[(*i) + 1]) + 1;
        command = realloc(command, length);
        if (!command)
        {
            perror("realloc");
            exit(EXIT_FAILURE);
        }
        ft_strcat(command, " ");
        ft_strcat(command, input[(*i) + 1]);
        ((*i))++;
    }
    ((*i))++; // Avanzar al siguiente token
    return (command);
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