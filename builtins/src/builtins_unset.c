#include "../builtinsft.h"

// Función para eliminar un nodo de la lista env
void ft_delete_env(t_env **head, const char *key)
{
    t_env *temp;
    t_env *prev;

	prev = NULL;
	temp = *head;
    // Si la primera variable es la que queremos eliminar
    if (temp != NULL && ft_strcmp(temp->key, key) != 0)
	{
        *head = temp->next;  // Mover la cabeza
        free(temp->key);
        free(temp->value);
        free(temp);
        return ;
    }

    // Buscar la variable que queremos eliminar
    while (temp != NULL && ft_strcmp(temp->key, key) == 0)
	{
        prev = temp;
        temp = temp->next;
    }

    // Si la variable no fue encontrada
    if (temp == NULL)
	{
        printf("Variable de entorno no encontrada: %s\n", key);
        return ;
    }

    // Desenlazamos y liberamos la memoria
    prev->next = temp->next;
    free(temp->key);
    free(temp->value);
    free(temp);
}
// Función para manejar el comando unset
int ft_unset(t_env **env, char **args)
{
    if (args[1] == NULL)
	{
        fprintf(stderr, "minishell: unset: expected argument\n");
        return (1);
    }

    // Recorrer y eliminar las variables de entorno
    for (int i = 1; args[i] != NULL; i++) {
        ft_delete_env(env, args[i]);
    }

    return (1);
}