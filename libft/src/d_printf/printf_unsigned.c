#include "../../libft.h"

static int	ft_putunsigned_printf(unsigned int n)
{
	int count = 0;

	if (n >= 10)
		count += ft_putunsigned_printf(n / 10);
	count += ft_putchar_printf(n % 10 + '0');
	return count;
}

int ft_handle_unsigned(va_list args)
{
	unsigned int n;

	n = va_arg(args, unsigned int);
	return (ft_putunsigned_printf(n));
}
