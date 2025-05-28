#include "../../libft.h"

int ft_handle_pointer(va_list args)
{
	unsigned long ptr;
	int count;

	count = 0;
	ptr = (unsigned long)va_arg(args, void *);
	count += write(1, "0x", 2);
	count += ft_puthex_printf(ptr, 0);
	return (count);
}
