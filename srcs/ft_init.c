# include "../include/cub3D.h"

void	initmlx(t_all *all)
{
	if (!(all->mlx.imgptr = mlx_new_image(all->mlx.ptr,
			all->info.res.x, all->info.res.y)))
	{
		ft_printf("Error\nmlx_new_image");
		ft_exit(all);
	}
	if (!(all->mlx.get_data = (int *)mlx_get_data_addr(all->mlx.imgptr,
			&all->mlx.bits_per_pixel, &all->mlx.size_line, &all->mlx.endian)))
	{
		ft_printf("mlx_get_data_addr");
		ft_exit(all);
	}
}

void initwindow(t_all *all)
{
	if ((all->cam.isit != 1))
	{
		 ft_printf(ERROR_PLAYER, all->cam.isit);
		 ft_exit(all);
	}
	if (!(all->mlx.ptr = mlx_init()))
	{
		ft_printf("Error\nmlx_init");
		ft_exit(all);
	}
	if (!(all->mlx.winptr = mlx_new_window(all->mlx.ptr,
			all->info.res.x, all->info.res.y, "cub3D")))
	{
		ft_printf("Error\nmlx_init");
		ft_exit(all);
	}
}

t_mlx			resize_image(t_all *all, int width, int height)
{
	t_mlx	tmp;
	double	size_x;
	double	size_y;
	int		x;
	int		y;

	size_x = (all->hand.h / (double)width);
	size_y = (all->hand.w / (double)height);
	tmp.imgptr = mlx_new_image(all->mlx.ptr, width, height);
	all->hand.get_data = (int *)mlx_get_data_addr(all->hand.imgptr,
			&all->hand.bits_per_pixel, &all->hand.size_line, &all->hand.endian);
	tmp.get_data = (int*)mlx_get_data_addr(tmp.imgptr, &(tmp.bits_per_pixel), &(tmp.size_line),
			&(tmp.endian));
	y = -1;
	while (++y < height)
	{
		x = -1;
		while (++x < width)
		{
			tmp.get_data[x + (y * tmp.size_line / 4)] =
				all->hand.get_data[(int)(((int)(x * size_x) + ((int)(y * size_y) * (all->hand.size_line / 4))))];
		}
	}
	tmp.h = height;
	tmp.w = width;
	return (tmp);
}

void	load_data(t_all *all)
{
	all->hand.imgptr = mlx_xpm_file_to_image(all->mlx.ptr, "./objet/handsim.xpm", &all->hand.h , &all->hand.w);
}

void			load_textures(t_all *all)
{
	t_mlx tmp;

	load_data(all);
	tmp = resize_image(all, all->info.res.x * 0.6, all->info.res.x * 0.6);
	mlx_destroy_image(all->mlx.ptr, all->hand.imgptr);
	all->hand = tmp;
}

void	ft_draw_hand(t_all *all)
{
	t_coor		img;
	t_dcoor		text;
	t_dcoor		taille;

	taille.x =  ((double)all->hand.w / (double)all->info.res.x);
	taille.y =  ((double)all->hand.h / (double)all->info.res.y);
	img.x = 0;
	text.x = 0;
	while (img.x < all->info.res.x - 1)
	{
		img.y = 0;
		text.y = 0;
		while (img.y < all->info.res.y)
		{
			all->hand.color = all->hand.get_data[(int)text.y * all->hand.w +
				(int)text.x];
			all->mlx.get_data[img.y * all->info.res.x + img.x] = all->hand.color;
			img.y++;
			text.y += taille.y;
		}
		img.x++;
		text.x += taille.x;
	}
	mlx_put_image_to_window(all->mlx.ptr, all->mlx.winptr,
			all->hand.imgptr, all->info.res.x * 0.5, all->info.res.y * 0.36);
}

void	ft_refresh(t_all *all)
{

initmlx(all);
	ft_reycasting(all);
	ft_sprites(all);
	mlx_put_image_to_window(all->mlx.ptr, all->mlx.winptr, all->mlx.imgptr, 0, 0);
	draw_vie(all);
 	load_textures(all);
	ft_draw_hand(all);
	mlx_destroy_image(all->mlx.ptr, all->mlx.imgptr);
}

void	initall(t_all *all, char **argv)
{
	ft_memset(all, 0, sizeof(t_all));
	all->cam.speed = 0.13;
	ft_parsing(argv, all);
	initwindow(all);
	ft_textures(all);
	ft_refresh(all);
}
