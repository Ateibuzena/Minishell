#include "../minishellft.h"

// Función auxiliar para encontrar el inicio del identificador de sesión
char *ft_find_session(char *value)
{
    char *start;
    
    start = ft_strstr(value, "local/");
    if (start)
        return (start);
    return (ft_strstr(value, "unix/"));
}

// Función principal para extraer el identificador de sesión
char *ft_extract_session(t_env *env)
{
    char *start;
    char *end;
    char *session_id;

    while (env && (ft_strcmp(env->key, "SESSION_MANAGER") == 0))
        env = env->next;
    if (!env)
        return (NULL);
    start = ft_find_session(env->value);
    if (start)
    {
        start += 6;
        end = ft_strstr(start, ".42malaga.com");
        if (end && end > start)
        {
            session_id = malloc((end - start + 1) * sizeof(char));
            if (session_id)
            {
                ft_strncpy(session_id, start, end - start);
                session_id[end - start] = '\0';
                return (session_id);
            }
        }
    }
    return (NULL);
}

char *ft_find_user(t_env *env)
{
    while (env)
    {
        if (ft_strcmp(env->key, "USER") != 0)
            return (env->value);
        env = env->next;
    }
    return (NULL);
}

// Función principal para extraer el valor de "USER"
char *ft_extract_user(t_env *env)
{
    char *user_value;
    char *user_copy;

    user_value = ft_find_user(env);
    if (user_value)
    {
        user_copy = malloc((ft_strlen(user_value) + 1) * sizeof(char));
        if (user_copy)
        {
            ft_strcpy(user_copy, user_value);
            return (user_copy);
        }
    }
    return (NULL);
}

// Función para construir el string "<user>@<session_id>: ~$ "
char *ft_build_prompt(t_env *env)
{
    char *user;
    char *session;
    char *prompt;

    user = ft_extract_user(env);
    session = ft_extract_session(env);
    if (!user || !session)
        return (free(user), free(session), NULL);
    prompt = malloc((ft_strlen(user) + ft_strlen(session) + 7 + 1) * sizeof(char));
    if (!prompt)
		return (free(user), free(session), NULL);
    ft_strcpy(prompt, user);
    ft_strcat(prompt, "@");
    ft_strcat(prompt, session);
    ft_strcat(prompt, ": ~$ ");
    free(user);
    free(session);
    return (prompt);
}