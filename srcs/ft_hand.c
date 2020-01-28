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

void			load_textures(t_all *all)
{
	t_mlx tmp;

	all->hand.imgptr = mlx_xpm_file_to_image(all->mlx.ptr, "./objet/handsim.xpm", &all->hand.h , &all->hand.w);
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
