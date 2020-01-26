# include "../include/cub3D.h"

void	sp_position(t_all *all, int i, t_spr *spr)
{
	double invdet;

	spr->camsp.x = all->sprites[all->sprites[i].ordre].coor.x - all->cam.pos.x;
	spr->camsp.y = all->sprites[all->sprites[i].ordre].coor.y - all->cam.pos.y;
	invdet = 1.0 / (all->algo.plane.x * all->cam.ori.y - all->algo.plane.y * all->cam.ori.x);
	spr->trans.x = invdet * (all->cam.ori.y * spr->camsp.x - all->cam.ori.x * spr->camsp.y);
	spr->trans.y = invdet * (-all->algo.plane.y * spr->camsp.x + all->algo.plane.x * spr->camsp.y);
	spr->spscreen = (int)((all->info.res.x / 2) * (1.0 + spr->trans.x / spr->trans.y));
}

void	sp_dimension(t_all *all, t_spr *spr)
{

	spr->sph = abs((int)(all->info.res.y / spr->trans.y));
	spr->start.y = -spr->sph / 2 + all->info.res.y / 2;
	if (spr->start.y < 0)
		spr->start.y = 0;
	spr->end.y = spr->sph / 2 + all->info.res.y / 2;
	if (spr->end.y >= all->info.res.y)
		spr->end.y = all->info.res.y - 1;
	spr->spw = abs((int)(all->info.res.y / spr->trans.y));
	spr->start.x = -spr->spw / 2 + spr->spscreen;
	if (spr->start.x < 0)
		spr->start.x = 0;
	spr->end.x = spr->spw / 2 + spr->spscreen;
	if (spr->end.x >= all->info.res.x)
		spr->end.x = all->info.res.x - 1;
}

void	get_color(t_all *all, int x, int y, int i, t_spr *spr)
{
	(void)spr;
	if (x >= 0 && x < all->sprites[i].img.w && y >= 0 && y < all->sprites[i].img.h)
	{
		all->sprites[i].img.color = *(int*)(all->sprites[i].img.ptr
				+ (x * all->sprites[i].img.bits_per_pixel / 8 + y * all->sprites[i].img.size_line));
	}
	else
		all->sprites[i].img.color = 0x0;
}

void	color_dist(t_all *all, double dis, int i, t_spr *spr)
{
	(void)spr;
	if (dis > 2.0)
	{
		all->sprites[i].img.color = 
		(((int)(((all->sprites[i].img.color & 0xFF0000) >> 16) / 256) |
		((int)(((all->sprites[i].img.color & 0x00FF00) >> 8) / 256) |
		(int)((all->sprites[i].img.color & 0x0000FF) / 256))));
	}
}

void	draw_pix(t_all *all, int x, int y, int i, t_spr *spr)
{

	(void)spr;
	if (x >= 0 && x < all->info.res.x && y >= 0 && y < all->info.res.y)
//		*(int*)(all->mlx.imgptr + (all->info.res.x * y + x) *
//				all->mlx.bits_per_pixel / 8) = spr->sp_odre[i].color;
	all->mlx.get_data[x + y * (all->mlx.size_line / 4)] = all->sprites[i].img.color;
//		all->mlx.get_data[x + y * (all->mlx.size_line / 4)] = spr->sp_odre[i].data[spr->texsp.x + spr->texsp.y * all->texture.w];
//	printf("spr->sp_odre[i].color%d\n", spr->sp_odre[i].color);
}

void	sp_draw(t_all *all, int x, int i, t_spr *spr)
{
	int y;
	int d;

	y = spr->start.y;
	while (y < spr->end.y)
	{
		d = (y * 256 - all->info.res.y * 128 + spr->sph * 128);
		spr->texsp.y = (d * all->sprites[i].img.h / spr->sph) / 256;
		get_color(all, spr->texsp.x, spr->texsp.y, i, spr);
		color_dist(all, all->sprites[i].dist / 4, i, spr);
		if (spr->trans.y < spr->distwall[x])
//			draw_pix(all, x, y, i, spr);
			all->mlx.get_data[x + y * (all->mlx.size_line / 4)] = all->sprites[i].img.color;
		y++;
	}
}

void		ft_sort(t_all *all, t_spr *spr)
{
	int i;

	i = 0;
	while (i < spr->nbsp)
	{
		all->sprites[i].ordre = i;
		all->sprites[i].dist = ft_power(all->cam.pos.x - all->sprites[i].coor.y, 2)
			+ ft_power(all->cam.pos.y - all->sprites[i].coor.y, 2);
		i++;
	}
}

void		ft_sort_sp(t_all *all, t_spr *spr)
{
	int tmp;
	int i;

	i = 0;
	while (i + 1 < spr->nbsp)
	{
		if (all->sprites[all->sprites[i].ordre].dist < all->sprites[all->sprites[i + 1].ordre].dist)
		{
			tmp = all->sprites[i].ordre;
			all->sprites[i].ordre = all->sprites[i + 1].ordre;
			all->sprites[i + 1].ordre = tmp;
			ft_sort_sp(all, spr);
		}
		i++;	
	}
}

void	init_sprites(t_all *all, t_spr *spr)
{
	int i;
	int x;

	ft_sort(all, spr);
	ft_sort_sp(all, spr);
	i = 0;
	while (i < spr->nbsp)
	{
		sp_position(all, i, spr);
		sp_dimension(all, spr);
		x = spr->start.x;
		while (x < spr->end.x && x < all->info.res.x)
		{
			spr->texsp.x = (int)(256 * (x - (-spr->spw / 2 + spr->spscreen)) *
					all->sprites[i].img.w / spr->spw) / 256;
			if (spr->trans.y > 0)
				sp_draw(all, x, i, spr);
			x++;
		}
		i++;
	}
}

void		ft_sprites(t_all *all, t_spr *spr)
{
	int x;
	int y;
	int i;

	y = 0;
	i = 0;
//	printf("all->info.bufmap %s\n", all->info.bufmap);
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
	init_sprites(all, spr);
}
