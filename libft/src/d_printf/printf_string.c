#include "../../libft.h"

int	ft_putstr_printf(char *s)
{
	int i;

	i = 0;
	if (!s)
		return (write(1, "(null)", 6));
	while (s[i])
		write(1, &s[i++], 1);
	return (i);
}

int ft_handle_string(va_list args)
{
	char *s;

	s = va_arg(args, char *);
	return (ft_putstr_printf(s));
}
