# include "../include/cub3D.h"

void	sprite_position(t_cub3d *cub, int i)
{
	double invdet;

	all->info.camsp.x = all->info.srite[all->info.sp_odre].x - all->cam.pos.x;
	all->info.camsp.y = all->info.srite[all->info.sp_odre].y - all->cam.pos.y;
	invdet = 1.0 / (all->algo.plane.x * all->cam.ori.y - all->algo.plane.y * all->cam.ori.x);
	all->info.trans.x = invdet * (all->cam.ori.y * all->info.camsp.x - all->cam.ori.x * all->info.camsp.y);
	all->info.trans.y = invdet * (-all->algo.plane.y * all->info.camsp.x + all->algo.plane.x * all->info.camsp.y);
	all->info.spscreen = (int)((all->info.res.x / 2) * (1.0 + all->info.trans.x / all->info.trans.y));
}

static void	sprite_dimensions(t_cub3d *cub)
{

	cub->spr.sp_h = abs((int)(cub->res_y / all->info.trans.y));
	cub->spr.sp_w = abs((int)(cub->res_y / all->info.trans.y));
	cub->spr.draw_starty = -cub->spr.sp_h / 2 + cub->res_y / 2;
	if (cub->spr.draw_starty < 0)
		cub->spr.draw_starty = 0;
	cub->spr.draw_endy = cub->spr.sp_h / 2 + cub->res_y / 2;
	if (cub->spr.draw_endy >= cub->res_y)
		cub->spr.draw_endy = cub->res_y - 1;
	cub->spr.draw_startx = -cub->spr.sp_w / 2 + cub->spr.sp_screen;
	if (cub->spr.draw_startx < 0)
		cub->spr.draw_startx = 0;
	cub->spr.draw_endx = cub->spr.sp_w / 2 + cub->spr.sp_screen;
	if (cub->spr.draw_endx >= cub->res_x)
		cub->spr.draw_endx = cub->res_x - 1;
}

static void	draw_sprites(t_cub3d *cub, int x, int i)
{
	int y;
	int d;

	y = cub->spr.draw_starty;
	while (y < cub->spr.draw_endy)
	{
		d = y * 256 - (cub->res_y - cub->spr.sp_h) * 128;
		cub->spr.tsp_y = ((d * cub->tex[6].height) / cub->spr.sp_h) / 256;
		get_color(cub, 6, cub->spr.tsp_x, cub->spr.tsp_y);
		color_dist(cub, 6, cub->spr.sp_dist[i] / 4);
		if (cub->tex[6].color != 0x0 \
			&& cub->spr.trans_y < cub->spr.distbuf[x])
			draw_pix(cub, 6, x, y);
		y++;
	}
}

void		ft_sort(t_all *all)
{
	int i;

	i = 0;
	while (i < all->info.nbsp)
	{
		all->info.sp_odre[i] = i;
		all->info.sp_dist[i] = ft_power(all->cam.pos.x - all->info.srite[i].x, 2)
			+ ft_power(all->cam.pos.y - all->info.sprite[i].y, 2);
		i++;
	}
}

void		ft_sort_sp(t_all *all)
{
	int tmp;
	int i;
	int j;
	double temp;
	int tmpint;

	tmp = amount;
	while (tmp > 1 || swapped == 1)
	{
		tmp = tmp * 10 / 13;
		if (tmp == 9 || tmp == 10)
			tmp = 11;
		if (tmp < 1)
			tmp = 1;
		i = -1;
		while (++i < amount - tmp)
		{
			j = i + tmp;
			if (all->info.sp_dist[i] < all->info.sp_dist[j])
			{
				temp = all->info.sp_dist[i];
				all->info.sp_dist[i] = all->info.sp_dist[j];
				all->info.sp_dist[j] = temp;
				tmpint = all->info.sp_odre[i];
				all->info.sp_odre[i] = all->info.sp_odre[j];
				all->info.sp_odre[j] = all->info.sp_odret;
				ft_sort_sp(order, dist, amount);
			}
		}
	}

void	init_sprites(t_all *all)
{
	int i;
	int x;

	ft_sort(all);
	ft_sort_sp(all);
	i = 0;
	while (i < all->info.nbsp)
	{
		sprite_position(all, i);
		sprite_dimensions(all);
		x = cub->spr.draw_start;
		while (x < cub->spr.draw_endx && x < cub->res_x)
		{
			cub->spr.tsp_x = (int)(256 * \
				(x - (-cub->spr.sp_w / 2 + cub->spr.sp_screen)) * \
				cub->tex[6].width / cub->spr.sp_w) / 256;
			if (cub->spr.trans_y > 0)
				draw_sprites(cub, x, i);
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

	x = 0;
	i = 0;
	while (x < all->info.res.x)
	{
		y = 0;
		while (y < all->info.res.y)
		{
			if (all->info.bufmap[x + (y * all->info.maplen.x)] == '2')
				all->info.sprite[i++] = (t_coor){x + 0.5, y + 0.5};
			y++;
		}
		x++;
	}
//	init_sprites(all);
}
