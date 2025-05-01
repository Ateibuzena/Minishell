#include "../minishellft.h"

int main(int argc, char **argv, char **envp)
{
	char *prompt;
    char *input;
    t_History *history;
    t_Env *env;
	char *cleaned;
	char *expanded;
	char *normalized;
	int status = 0;

    if (argc > 1)
		return (ft_perror("minishell error: arguments\n"), !status);
    (void)argv;
    //CONFIGURAR SEÑALES
	ft_setup_signals();
    // Copiar el entorno y asignar memoria para el historial
    env = ft_copy_env(envp);
    
    history = (t_History *)malloc(sizeof(t_History));
    if (!history)
    	return (ft_perror("Malloc error: History\n"), !status);
    ft_init_history(history);
    while (1)
    {
        // Construir el prompt
        prompt = ft_prompt(env);
		*get_g_in_readline() = 1;
        input = readline(prompt);
		*get_g_in_readline() = 0;  // <-- saliste de readline
        free(prompt);
        //fprintf(stderr, "\nInput: %s\n", input);
        // Salir si la entrada es NULL (Ctrl+D)
        if (!input)
		{
			write(1, "exit\n", 5);
        	break ;
		}
		if (input[0] == '\0')
		{
			free(input);
			continue ;
		}
		// Agregar la entrada al historial
		ft_add_entry(history, input);
		//ft_show_history(history);
        normalized = ft_normalize_input(input);
		free(input);
		
        if (!normalized || normalized[0] == '\0')
		{
			ft_perror("minishell error: normalize\n");
			continue ;
		}
        // Procesar entrada si no está vacía
		// 1. Validar sintaxis de la línea original
		if (!validate_syntax(normalized))
		{
			ft_perror("minishell: syntax error\n");
			free(normalized);
			continue ;
		}

		// 2. Expandir variables
		expanded = ft_expand_variables(normalized, env, status); // suponiendo que tienes last_exit global
		
		free(normalized);
		if (!expanded)
		{
			ft_perror("minishell error: expand\n");
			continue ;
		}

		// 3. Manejar comillas
		cleaned = ft_handle_quotes(expanded);
	
		free(expanded);
		if (!cleaned)
		{
			ft_perror("minishell error: handle_quotes\n");
			continue ;
		}
	
		// 4. Ejecutar comandos (pipes o builtin)
		if (cleaned[0] != '\0')
			status = ft_handle_pipes(cleaned, history, env);
    }
    ft_free_history(history);
    ft_free_env(env);
    return (0);
}
