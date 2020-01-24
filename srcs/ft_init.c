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

void	ft_refresh(t_all *all)
{
	t_texture test;

	initmlx(all);
	ft_reycasting(all);
	ft_sprites(all);
	mlx_put_image_to_window(all->mlx.ptr, all->mlx.winptr, all->mlx.imgptr, 0, 0);
	test.data = mlx_xpm_file_to_image(all->mlx.ptr, "./objet/hand.xpm", &(test.h) , &(test.w));
	test.h = all->info.res.y / 3;
	test.w = all->info.res.y / 3;
	mlx_put_image_to_window(all->mlx.ptr, all->mlx.winptr, test.data, 50, all->info.res.y / 1.89);
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
