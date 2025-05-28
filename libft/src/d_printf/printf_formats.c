#include "../../libft.h"

int ft_init_handlers(t_format **head)
{
    *head = NULL;
    if (!ft_add_handler(head, 'c', ft_handle_char))
        return (0);
    if (!ft_add_handler(head, 's', ft_handle_string))
        return (0);
    if (!ft_add_handler(head, 'd', ft_handle_digits))
        return (0);
    if (!ft_add_handler(head, 'i', ft_handle_integer))
        return (0);
    if (!ft_add_handler(head, 'u', ft_handle_unsigned))
        return (0);
    if (!ft_add_handler(head, 'x', ft_handle_hex_lower))
        return (0);
    if (!ft_add_handler(head, 'X', ft_handle_hex_upper))
        return (0);
    if (!ft_add_handler(head, 'p', ft_handle_pointer))
        return (0);
    if (!ft_add_handler(head, '%', ft_handle_percent))
        return (0);
    return (1);
}

int ft_add_handler(t_format **lst, char id, int (*func)(va_list))
{
    t_format *new_node;

    new_node = malloc(sizeof(t_format));
    if (!new_node)
        return (0);
    new_node->id = id;
    new_node->func = func;
    new_node->next = *lst;
    *lst = new_node;
    return (1);
}

void ft_free_handlers(t_format *list)
{
    t_format *tmp;

    while (list)
    {
        tmp = list;
        list = list->next;
        free(tmp);
        tmp = NULL;
    }
    free(list);
    list = NULL;
}

int ft_call_handler(t_format *handlers, char id, va_list args)
{
    while (handlers)
    {
        if (handlers->id == id)
            return (handlers->func(args));
        handlers = handlers->next;
    }
    return (0);
}
