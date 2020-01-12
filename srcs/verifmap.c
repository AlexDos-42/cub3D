# include "../include/cub3D.h"

void		posdepart(t_all *all, int x, int y, char dir)
{
	all->cam.pos.x = x;
	all->cam.pos.y = y;
	if (dir == 'E')
	{
		all->cam.ori.x = 1;
		all->cam.ori.y = 0;
	}
	else if (dir == 'S')
	{
		all->cam.ori.x = 0;
		all->cam.ori.y = 1;
	}
	else if (dir == 'W')
	{
		all->cam.ori.x = -1;
		all->cam.ori.y = 0;
	}
	else
	{
		all->cam.ori.x = 0;
		all->cam.ori.y = -1;
	}
	all->algo.plane.x = all->cam.ori.y;
	all->algo.plane.y = -all->cam.ori.x;
	all->cam.isit++;
}

void     ft_checkline(char *line, int j, t_all *all)
{;
	int			i;
	int			k;

	i = -1;
	while (++i < all->info.maplen.x)
	{
		k = i + (j * all->info.maplen.x);
		if (line[k] == 'N' || line[k] == 'S' || line[k] == 'W' || line[k] == 'E')
			posdepart(all, i, j, line[k]);
		else if (line[k] == '2')
			all->info.nbbloc++;
		else if (line[k] != '1' && line[k] != '0')
		{
			printf(ERROR_MAP, line[k]);
			ft_exit(all);
		}
	}
}

void	verify_map(t_all *all)
{
    int		j;
    char *tmp;

    j = -1;
	tmp = all->info.bufmap;
    while (++j < all->info.maplen.y)
		ft_checkline(tmp, j, all);
}
