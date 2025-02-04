char **ft_tokenizer(char *entry)
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
        if (ft_strcmp(input[i], "<") != 0 || ft_strcmp(input[i], ">") != 0
            || ft_strcmp(input[i], "<<") != 0 || ft_strcmp(input[i], ">>") != 0)
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
            printf("input[i]: %s\n", input[i]);
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
                    && ft_strcmp(input[i + 1], ">") == 0
                    && ft_strcmp(input[i + 1], ">>") == 0)
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
            printf("result[j]: %s\n", result[j]);
            i++; // Avanzar al siguiente token
        }
        j++;
    }

    result[j] = NULL; // Terminar el array con NULL
    ft_freedouble(input);
    return result;
}