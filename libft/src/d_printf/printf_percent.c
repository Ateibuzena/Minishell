#include "../../libft.h"

int ft_handle_percent(va_list args)
{
	(void)args;
	return (write(1, "%", 1));
}
