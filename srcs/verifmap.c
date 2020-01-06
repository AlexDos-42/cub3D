# include "../include/cub3D.h"

void		posdepart(t_all *all, int x, int y, char dir)
{
	all->cam.posX = x;
	all->cam.posY = y;
	if (dir == 'E')
	{
		all->cam.oriX = 1;
		all->cam.oriY = 0;
	}
	else if (dir == 'S')
	{
		all->cam.oriX = 0;
		all->cam.oriY = 1;
	}
	else if (dir == 'W')
	{
		all->cam.oriX = -1;
		all->cam.oriY = 0;
	}
	else
	{
		all->cam.oriX = 0;
		all->cam.oriY = -1;
	}
	all->cam.isit = 1;
}

int     ft_checkline(char *line, int j, t_all *all)
{
	static int	l;
	int			i;
	int			k;

	i = -1;
	while (all->info.maplenx[++i])
	{
		k = i + (j * all->info.maplenx[i]);
		if (line[k] == 'N' || line[k] == 'S' || line[k] == 'W' || line[k] == 'E')
			posdepart(all, i, j, line[k]);
		else if (line[k] == '2')
		{
			all->info.blocx[l] = i;
			all->info.blocy[l++] = j;
		}
		else if (line[k] != '1' && line[k] != '0')
			return (0);
	}
	return (1);
}

int		verify_map(t_all *all)
{
    int		j;
    char *tmp;

    j = 0;
    tmp = all->info.bufmap;
    while (++j < all->info.mapleny)
	{
		if (!(ft_checkline(tmp, j, all)) || all->cam.isit != 1)
			return (0);
	}
	return (1);
}