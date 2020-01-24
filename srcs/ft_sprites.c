# include "../include/cub3D.h"

void	sp_position(t_all *all, int i)
{
	double invdet;

	all->spr.camsp.x = all->spr.sprite[all->spr.sp_odre[i].o].x - all->cam.pos.x;
	all->spr.camsp.y = all->spr.sprite[all->spr.sp_odre[i].o].y - all->cam.pos.y;
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
	if (x >= 0 && x < all->spr.sp_odre[i].w && y >= 0 && y < all->spr.sp_odre[i].h)
	{
		all->spr.sp_odre[i].color = *(int*)(all->spr.sp_odre[i].ptr
				+ (x * all->spr.sp_odre[i].bpp / 8 + y * all->spr.sp_odre[i].line_size));
	}
	else
		all->spr.sp_odre[i].color = 0x0;
}

void	color_dist(t_all *all, double dis, int i)
{
	if (dis > 2.0)
	{
		all->spr.sp_odre[i].color = 
		(((int)(((all->spr.sp_odre[i].color & 0xFF0000) >> 16) / (dis / 2.0)) << 16) |
		((int)(((all->spr.sp_odre[i].color & 0x00FF00) >> 8) / (dis / 2.0)) << 8) |
		(int)((all->spr.sp_odre[i].color & 0x0000FF) / (dis / 2.0)));
	}
}

void	draw_pix(t_all *all, int x, int y, int i)
{

	if (x >= 0 && x < all->info.res.x && y >= 0 && y < all->info.res.y)
		*(int*)(all->mlx.imgptr + (all->info.res.x * y + x) *
				all->mlx.bits_per_pixel / 8) = all->spr.sp_odre[i].color;
//		all->mlx.get_data[x + y * (all->mlx.size_line / 4)] = all->spr.sp_odre[i].data[all->spr.texsp.x + all->spr.texsp.y * all->texture.w];
//	printf("all->spr.sp_odre[i].color%d\n", all->spr.sp_odre[i].color);
}

void	sp_draw(t_all *all, int x, int i)
{
	int y;
	int d;

	y = all->spr.start.y;
	while (y < all->spr.end.y)
	{
		d = (y * 256 - all->info.res.y * 128 + all->spr.sph * 128);
		all->spr.texsp.y = (d * all->spr.sp_odre[i].h / all->spr.sph) / 256;
		get_color(all, all->spr.texsp.x, all->spr.texsp.y, i);
		color_dist(all, all->spr.sp_dist[i] / 4, i);
//		if (all->spr.trans.y < all->spr.distwall[x])
//			draw_pix(all, x, y, i);
		all->mlx.get_data[x + y * (all->mlx.size_line / 4)] = all->spr.sp_odre[i].color;
		y++;
	}
}

void		ft_sort(t_all *all)
{
	int i;

	i = 0;
	while (i < all->spr.nbsp)
	{
		all->spr.sp_odre[i].o = i;
		all->spr.sp_dist[i] = ft_power(all->cam.pos.x - all->spr.sprite[i].x, 2)
			+ ft_power(all->cam.pos.y - all->spr.sprite[i].y, 2);
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
		if (all->spr.sp_dist[all->spr.sp_odre[i].o] < all->spr.sp_dist[all->spr.sp_odre[i + 1].o])
		{
			tmp = all->spr.sp_odre[i].o;
			all->spr.sp_odre[i].o = all->spr.sp_odre[i + 1].o;
			all->spr.sp_odre[i + 1].o = tmp;
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
		all->spr.sp_odre[i] = all->textureI;
		sp_position(all, i);
		sp_dimension(all);
		x = all->spr.start.x;
		while (x < all->spr.end.x && x < all->info.res.x)
		{
			all->spr.texsp.x = (int)(256 * (x - (-all->spr.spw / 2 + all->spr.spscreen)) *
					all->spr.sp_odre[i].w / all->spr.spw) / 256;
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
	printf("all->info.bufmap %s\n", all->info.bufmap);
	while (y < all->info.maplen.y)
	{
		x = 0;
		while (x < all->info.maplen.x) 
		{
			if (all->info.bufmap[x + (y * all->info.maplen.x)] == '2')
			{
				all->spr.sprite[i] = (t_coor){x + 0.5, y + 0.5};
				i++;
			}
			x++;
		}
		y++;
	}
	init_sprites(all);
}
