# include "../include/cub3D.h"

void	ft_checkones(t_all *all)
{
	int x;
	int y;

	x = -1;
	while (++x < all->info.maplen.x)
	{
		if (all->info.bufmap[x] != '1' || all->info.bufmap[x + (all->info.maplen.x * all->info.maplen.y) - all->info.maplen.x] != '1' )
		{
			printf("Error map ; Only '1' on the edges of your map");
			ft_exit(all);
		}
	}
	x = 0;
	y = 0;
//	while (y < all->info.maplen.y)
//	{
//		if (all->info.bufmap[x] || all->info.bufmap[x][ft_strlen(all->info.bufmap[x]) - 1] != '1')
//			ft_exit(all);
//		y++;
//	}
}

void		posdepart(t_all *all, int x, int y, char dir)
{
	all->cam.pos.x = x + 0.5;
	all->cam.pos.y = y + 0.5;
	if (dir == 'E')
		all->cam.ori = (t_dcoor){1, 0};
	else if (dir == 'S')
		all->cam.ori = (t_dcoor){0, 1};
	else if (dir == 'W')
		all->cam.ori = (t_dcoor){-1, 0};
	else
		all->cam.ori = (t_dcoor){0, -1};
	all->algo.plane.x = -0.66 * all->cam.ori.y;
	all->algo.plane.y = 0.66 * all->cam.ori.x;
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
			all->spr.nbsp++;
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

	j = -1;
	while (++j < all->info.maplen.y)
		ft_checkline(all->info.bufmap, j, all);
	ft_checkones(all);
	all->sprites = (t_sprites*)ft_calloc(sizeof(t_sprites), all->spr.nbsp);
	all->spr.distwall = ft_calloc(sizeof(double*), all->info.res.x);
}
