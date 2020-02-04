/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hud.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alesanto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 14:51:07 by alesanto          #+#    #+#             */
/*   Updated: 2020/02/04 20:57:14 by alesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

t_mlx			resize_imagehud(t_all *all, int width, int height)
{
	t_mlx	tmp;
	double	size_x;
	double	size_y;
	int		x;
	int		y;

	size_x = (all->hud.h / (double)width);
	size_y = (all->hud.w / (double)height);
	tmp.imgptr = mlx_new_image(all->mlx.ptr, width, height);
	all->hud.get_data = (int *)mlx_get_data_addr(all->hud.imgptr,
		&all->hud.bits_per_pixel, &all->hud.size_line, &all->hud.endian);
	tmp.get_data = (int*)mlx_get_data_addr(tmp.imgptr,
		&(tmp.bits_per_pixel), &(tmp.size_line), &(tmp.endian));
	y = -1;
	while (++y < height)
	{
		x = -1;
		while (++x < width)
			tmp.get_data[x + (y * tmp.size_line / 4)] = all->hud.get_data[(int)
				(int)(x * size_x) + (int)(y *
				size_y) * (all->hud.size_line / 4)];
	}
	tmp.h = height;
	tmp.w = width;
	return (tmp);
}

void			load_hudtex(t_all *all)
{
	t_mlx tmp;

	all->hud.imgptr = mlx_xpm_file_to_image(all->mlx.ptr,
			"./objet/hud.xpm", &all->hud.h, &all->hud.w);
	tmp = resize_imagehud(all, all->info.res.x + 2, all->info.res.y * 0.38);
	mlx_destroy_image(all->mlx.ptr, all->hud.imgptr);
	all->hud = tmp;
}

void			ft_draw_hud(t_all *all)
{
	t_coor		img;
	t_dcoor		text;
	t_dcoor		taille;

	taille.x = ((double)all->hud.w / (double)all->info.res.x);
	taille.y = ((double)all->hud.h / (double)all->info.res.y);
	img.x = -1;
	text.x = 0;
	while (++img.x < all->info.res.x - 1)
	{
		img.y = -1;
		text.y = 0;
		while (++img.y < all->info.res.y)
		{
			all->hud.color = all->hud.get_data[(int)text.y * all->hud.w +
				(int)text.x];
			all->mlx.get_data[img.y *
				all->info.res.x + img.x] = all->hud.color;
			text.y += taille.y;
		}
		text.x += taille.x;
	}
	mlx_put_image_to_window(all->mlx.ptr, all->mlx.winptr,
			all->hud.imgptr, -2, all->info.res.y * 0.63);
	mlx_destroy_image(all->mlx.ptr, all->hud.imgptr);
}
