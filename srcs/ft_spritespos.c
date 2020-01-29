# include "../include/cub3D.h"

void		ft_sort(t_all *all)
{
	int i;

	i = 0;
	while (i < all->spr.nbsp)
	{
		all->sprites[i].ordre = i;
		all->sprites[i].dist = ft_power(all->cam.pos.x - all->sprites[i].coor.y, 2)
			+ ft_power(all->cam.pos.y - all->sprites[i].coor.y, 2);
		i++;
	}
}

void		ft_sort_sp(t_all *all)
{
	int tmp;
	int i;

	i = 0;
	while (i + 1 < all->spr.nbsp)
	{
		if (all->sprites[all->sprites[i].ordre].dist < all->sprites[all->sprites[i + 1].ordre].dist)
		{
			tmp = all->sprites[i].ordre;
			all->sprites[i].ordre = all->sprites[i + 1].ordre;
			all->sprites[i + 1].ordre = tmp;
			ft_sort_sp(all);
		}
		i++;	
	}
}

void	sp_position(t_all *all, int i)
{
	double invdet;

	all->spr.camsp.x = all->sprites[all->sprites[i].ordre].coor.x - all->cam.pos.x;
	all->spr.camsp.y = all->sprites[all->sprites[i].ordre].coor.y - all->cam.pos.y;
	invdet = 1.0 / (all->algo.plane.x * all->cam.ori.y - all->algo.plane.y * all->cam.ori.x);
	all->spr.trans.x = invdet * (all->cam.ori.y * all->spr.camsp.x - all->cam.ori.x * all->spr.camsp.y);
	all->spr.trans.y = invdet * (-all->algo.plane.y * all->spr.camsp.x + all->algo.plane.x * all->spr.camsp.y);
	all->spr.spscreen = (int)((all->info.res.x / 2) * (1.0 + all->spr.trans.x / all->spr.trans.y));
}

void	sp_dimension(t_all *all)
{

	all->spr.sph = abs((int)(all->info.res.y / all->spr.trans.y));
	all->spr.start.y = -all->spr.sph / 2 + all->info.res.y / 2;
	if (all->spr.start.y < 0)
		all->spr.start.y = 0;
	all->spr.end.y = all->spr.sph / 2 + all->info.res.y / 2 ;
	if (all->spr.end.y >= all->info.res.y)
		all->spr.end.y = all->info.res.y - 1;
	all->spr.spw = abs((int)(all->info.res.y / all->spr.trans.y));
	all->spr.start.x = -all->spr.spw / 2 + all->spr.spscreen;
	if (all->spr.start.x < 0)
		all->spr.start.x = 0;
	all->spr.end.x = all->spr.spw / 2 + all->spr.spscreen;
	if (all->spr.end.x >= all->info.res.x)
		all->spr.end.x = all->info.res.x - 1;
}
