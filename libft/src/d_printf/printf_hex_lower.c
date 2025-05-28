#include "../../libft.h"

int	ft_puthex_printf(unsigned long n, int uppercase)
{
	int		count;
	char *base;

	if (uppercase)
		base = "0123456789ABCDEF";
	else
		base = "0123456789abcdef";
	count = 0;
	if (n >= 16)
		count += ft_puthex_printf(n / 16, uppercase);
	count += ft_putchar_printf(base[n % 16]);
	return (count);
}

int ft_handle_hex_lower(va_list args)
{
	unsigned int n;

	n = va_arg(args, unsigned int);
	return (ft_puthex_printf(n, 0));
}
