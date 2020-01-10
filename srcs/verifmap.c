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
	all->cam.isit++;
}

void     ft_checkline(char *line, int j, t_all *all)
{;
	int			i;
	int			k;

	i = -1;
	while (++i < all->info.maplenx)
	{
		k = i + (j * all->info.maplenx);
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
    while (++j < all->info.mapleny)
		ft_checkline(tmp, j, all);
}
