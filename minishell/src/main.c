#include "../minishellft.h"

char	*normalize_input(const char *input)
{
	int		i = 0;
	int		j = 0;
	char	*res = malloc(ft_strlen(input) * 3 + 1); // reserva de más por los espacios

	if (!res)
		return (NULL);

	while (input[i])
	{
		if ((input[i] == '|' || input[i] == '<' || input[i] == '>'))
		{
			// Manejar dobles redirecciones: << >>
			if ((input[i] == '<' || input[i] == '>') && input[i] == input[i + 1])
			{
				res[j++] = ' ';
				res[j++] = input[i++];
				res[j++] = input[i++];
				res[j++] = ' ';
			}
			else
			{
				res[j++] = ' ';
				res[j++] = input[i++];
				res[j++] = ' ';
			}
		}
		else
			res[j++] = input[i++];
	}
	res[j] = '\0';
	return (res);
}


int	is_quote(char c)
{
	return (c == '\'' || c == '"');
}

int	is_pipe(const char *s)
{
	return (ft_strcmp(s, "|") != 0);
}

int	is_redirection(const char *s)
{
	return (ft_strcmp(s, "<") != 0 || ft_strcmp(s, ">") != 0 ||
			ft_strcmp(s, ">>") != 0 || ft_strcmp(s, "<<") != 0);
}

int	is_operator(const char *s)
{
	return (!ft_strncmp(s, "||", 2) || !ft_strncmp(s, "&&", 2));
}

int	validate_quotes(const char *input)
{
	char	open = 0;

	while (*input)
	{
		if (is_quote(*input))
		{
			if (!open)
				open = *input;
			else if (*input == open)
				open = 0;
		}
		input++;
	}
	return (open == 0);
}

int	validate_tokens(char **tokens)
{
	int	i = 0;

	if (!tokens[0])
		return (0);

	// No puede empezar ni terminar con una pipe
	if (is_pipe(tokens[0]) || (tokens[1] == NULL && is_pipe(tokens[0])))
		return (0);

	while (tokens[i])
	{
		// Detectar operadores no permitidos
		if (is_operator(tokens[i]))
			return (0);

		// Pipes seguidas no permitidas: |
		if (is_pipe(tokens[i]) && tokens[i + 1] && is_pipe(tokens[i + 1]))
			return (0);

		// Redirecciones sin argumento después o con otra redirección justo después
		if (is_redirection(tokens[i]))
		{
			if (!tokens[i + 1] || is_redirection(tokens[i + 1]) || is_pipe(tokens[i + 1]))
				return (0);
		}
		i++;
	}
	return (1);
}

int	validate_syntax(char *input)
{
	char	**tokens;

	if (!validate_quotes(input))
		return (0);

	tokens = ft_split(input, ' ');
	if (!tokens)
		return (0);

	if (!validate_tokens(tokens))
	{
		ft_freedouble(tokens);
		return (0);
	}

	ft_freedouble(tokens);
	return (1);
}

int g_last_exit_code = 0;

int main(int argc, char **argv, char **envp)
{
    char *prompt;
    char *input;
    t_History *history;
    t_Env *env;
	char *cleaned;
	char *expanded;

    (void)argc;
    (void)argv;
    //CONFIGURAR SEÑALES
    // Copiar el entorno y asignar memoria para el historial
    env = ft_copy_env(envp);
    
    history = (t_History *)malloc(sizeof(t_History));
    if (!history)
    	return (ft_perror("Malloc error: History\n"), 1);
    ft_init_history(history);
    while (1)
    {
        // Construir el prompt
        prompt = ft_prompt(env);
        input = readline(prompt);
        //fprintf(stderr, "\nInput: %s\n", input);
        free(prompt);
        // Salir si la entrada es NULL (Ctrl+D)
        if (!input)
            continue ;
		ft_add_entry(history, input);
		//ft_show_history(history);
        char *normalized = normalize_input(input);
		fprintf(stderr, "\nNormalized: %s\n", normalized);
        if (!normalized || normalized[0] == '\0')
        {
            ft_perror("minishell: error al normalizar la entrada\n");
            free(input);
            continue ;
        }
        // Procesar entrada si no está vacía
		// 1. Validar sintaxis de la línea original
		if (!validate_syntax(normalized))
		{
			ft_perror("minishell: syntax error\n");
			free(normalized);
			free(input);
			continue ;
		}

		// 2. Expandir variables
		expanded = ft_expand_variables(normalized, env, g_last_exit_code); // suponiendo que tienes last_exit global
		fprintf(stderr, "\nExpanded: %s\n", expanded);
		free(normalized);
		if (!expanded || expanded[0] == '\0')
		{
			ft_perror("minishell: error al expandir variables\n");
			free(input);
			continue ;
		}

		// 3. Manejar comillas
		cleaned = ft_handle_quotes(expanded);
		fprintf(stderr, "\nCleaned: %s\n", cleaned);
		free(expanded);
		if (!cleaned || cleaned[0] == '\0')
		{
			ft_perror("minishell: error al manejar comillas\n");
			free(input);
			continue ;
		}
	
		// 4. Ejecutar comandos (pipes o builtin)
		if (cleaned[0] != '\0')
		{
			ft_handle_pipes(cleaned, history, env);
			free(cleaned);

		}
		free(input);
    }
    ft_free_history(history);
    ft_free_env(env);
    return (0);
}
