# include "../include/cub3D.h"

void	get_color(t_all *all, int i)
{
	if (all->sprites[i].img.get_data[all->spr.texsp.x
			+ all->spr.texsp.y * all->sprites[i].img.w] != -16777216)
			all->sprites[i].img.color =
				all->sprites[i].img.get_data[all->spr.texsp.x
				+ all->spr.texsp.y * all->sprites[i].img.w];
	else
		all->sprites[i].img.color = 0xBFD195;
}

void	sp_draw(t_all *all, int x, int i)
{
	int y;
	int d;

	y = all->spr.start.y;
	while (y < all->spr.end.y)
	{
		d = (y * 256 - all->info.res.y * 128 + all->spr.sph * 128);
		all->spr.texsp.y = (d * all->sprites[i].img.h / all->spr.sph) / 256;
		get_color(all, i);
		if (all->sprites[i].img.color != 0xBFD195 && all->spr.trans.y < all->spr.distwall[x])
		{
			if (x >= 0 && x < all->info.res.x && y >= 0 && y < all->info.res.y)
				all->mlx.get_data[x + y * (all->mlx.size_line / 4)] = all->sprites[i].img.color;
		}
		y++;
	}
}

void	init_sprites(t_all *all)
{
	int i;
	int x;

	ft_sort(all);
	ft_sort_sp(all);
	i = 0;
	while (i < all->spr.nbsp)
	{
		sp_position(all, i);
		sp_dimension(all);
		x = all->spr.start.x;
		while (x < all->spr.end.x && x < all->info.res.x)
		{
			all->spr.texsp.x = (int)(256 * (x - (-all->spr.spw / 2 + all->spr.spscreen)) *
					all->sprites[i].img.w / all->spr.spw) / 256;
			if (all->spr.trans.y > 0)
				sp_draw(all, x, i);
			x++;
		}
		i++;
	}
}

void		ft_sprites(t_all *all)
{
	int x;
	int y;
	int i;

	y = 0;
	i = 0;
	while (y < all->info.maplen.y)
	{
		x = 0;
		while (x < all->info.maplen.x) 
		{
			if (all->info.bufmap[x + (y * all->info.maplen.x)] == '2')
			{
				all->sprites[i].coor = (t_dcoor){x + 0.5, y + 0.5};
				i++;
			}
			x++;
		}
		y++;
	}
	init_sprites(all);
}
