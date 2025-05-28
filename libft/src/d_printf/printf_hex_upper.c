#include "../../libft.h"

int ft_handle_hex_upper(va_list args)
{
	unsigned int n;

	n = va_arg(args, unsigned int);
	return (ft_puthex_printf(n, 1));
}
