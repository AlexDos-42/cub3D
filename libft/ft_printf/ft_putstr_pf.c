#include "libft.h"

int	ft_putstr_pf(char *str, int fd)
{
	int i;

	if (!str)
		return (0);
	i = 0;
	if (fd == -1)
		write(1, "\0", 1);
	while (str[i])
	{
		write(1, &str[i], 1);
		i++;
	}
	if (fd == 1)
		write(1, "\0", 1);
	if (fd == 1 || fd == -1)
		i++;
	return (i);
}
