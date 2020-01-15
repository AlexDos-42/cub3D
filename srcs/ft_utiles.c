# include "../include/cub3D.h"

t_dcoor ft_dcoor(double x, double y)
{
	t_dcoor dcoor;
	
	dcoor.x = x;
	dcoor.y = y;
	return (dcoor);
}

t_coor	ft_coor(int x, int y)
{
	t_coor	coor;

	coor.x = x;
	coor.y = y;
	return (coor);
}

void     ft_exit(t_all *all)
{
	if (all->info.bufmap)
		free(all->info.bufmap);
	exit(0);
}

void     ft_ifspace(char *line, int *i)
{
	while ((line[*i] == ' ' || line[*i] == '\t' || line[*i] == '\n')
			|| (line[*i] == '\r' || line[*i] == '\v' || line[*i] == '\f'))
		(*i)++;
}
