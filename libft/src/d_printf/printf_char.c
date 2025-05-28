#include "../../libft.h"

int	ft_putchar_printf(char c)
{
	return (write(1, &c, 1));
}

int ft_handle_char(va_list args)
{
	char c;

	c = va_arg(args, int);
	return (ft_putchar_printf(c));
}
