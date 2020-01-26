# include "../include/cub3D.h"

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
	all->spr.end.y = all->spr.sph / 2 + all->info.res.y / 2;
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

void	get_color(t_all *all, int x, int y, int i)
{
	if (x >= 0 && x < all->sprites[i].img.w && y >= 0 && y < all->sprites[i].img.h)
	{
		all->sprites[i].img.color = *(int*)(all->sprites[i].img.ptr
				+ (x * all->sprites[i].img.bits_per_pixel / 8 + y * all->sprites[i].img.size_line));
	}
	else
		all->sprites[i].img.color = 0x0;
}

void	color_dist(t_all *all, double dis, int i)
{
	if (dis > 2.0)
	{
		all->sprites[i].img.color = 
		(((int)(((all->sprites[i].img.color & 0xFF0000) >> 16) / 256) |
		((int)(((all->sprites[i].img.color & 0x00FF00) >> 8) / 256) |
		(int)((all->sprites[i].img.color & 0x0000FF) / 256))));
	}
}

void	draw_pix(t_all *all, int x, int y, int i)
{

	if (x >= 0 && x < all->info.res.x && y >= 0 && y < all->info.res.y)
//		*(int*)(all->mlx.imgptr + (all->info.res.x * y + x) *
//				all->mlx.bits_per_pixel / 8) = all->spriptes[i].img.color;
	all->mlx.get_data[x + y * (all->mlx.size_line / 4)] = all->sprites[i].img.color;
//		all->mlx.get_data[x + y * (all->mlx.size_line / 4)] = spr->sp_odre[i].data[all->spr.texsp.x + all->spr.texsp.y * all->texture.w];
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
		get_color(all, all->spr.texsp.x, all->spr.texsp.y, i);
		color_dist(all, all->sprites[i].dist / 4, i);
		if (all->spr.trans.y < all->spr.distwall[x])
//			draw_pix(all, x, y, i);
			all->mlx.get_data[x + y * (all->mlx.size_line / 4)] = all->sprites[i].img.color;
		y++;
	}
}

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
				all->sprites[i].coor = (t_coor){x + 0.5, y + 0.5};
				i++;
			}
			x++;
		}
		y++;
	}
	init_sprites(all);
}
