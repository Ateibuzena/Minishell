#include "../../libft.h"

static int	ft_putnbr_printf(int n)
{
	long nb;
	int count;

	nb = n;
	count = 0;
	if (nb < 0)
	{
		count += write(1, "-", 1);
		nb = -nb;
	}
	if (nb >= 10)
		count += ft_putnbr_printf(nb / 10);
	count += ft_putchar_printf(nb % 10 + '0');
	return (count);
}

int ft_handle_digits(va_list args)
{
	int n;

	n = va_arg(args, int);
	return (ft_putnbr_printf(n));
}
