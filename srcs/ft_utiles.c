# include "../include/cub3D.h"

void     ft_exit(t_all *all)
{
	(void)all;
	exit(0);
}

void     ft_ifspace(char *line, int *i)
{
	while ((line[*i] == ' ' || line[*i] == '\t' || line[*i] == '\n')
			|| (line[*i] == '\r' || line[*i] == '\v' || line[*i] == '\f'))
		(*i)++;
}
