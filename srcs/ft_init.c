# include "../include/cub3D.h"

void	initmlx(t_all *all)
{
	if (!(all->mlx.ptr = mlx_init()))
	{
		ft_printf("Error\nmlx_init");
		ft_exit(all);
	}
	if (!(all->mlx.winptr = mlx_new_window(all->mlx.ptr, all->info.res.x, all->info.res.y, "cub3D")))
	{
		ft_printf("Error\nmlx_new_window");
		ft_exit(all);
	}
//	ft_textures(all);
	if (!(all->mlx.imgptr = mlx_new_image(all->mlx.ptr, all->info.res.x, all->info.res.y)))
	{
		ft_printf("Error\nmlx_new_image");
		ft_exit(all);
	}
	mlx_string_put(all->mlx.ptr, all->mlx.winptr, 400, 300, all->info.c, "bonjour");
	//	mlx_put_image_to_window (all->mlx.ptr, all->mlx.winptr,  all->mlx.imgptr, 0, 0);
	if (!(all->mlx.get_data = (int)mlx_get_data_addr(all->mlx.imgptr, &all->mlx.bits_per_pixel, &all->mlx.size_line, &all->mlx.endian)))
	{
		ft_printf("mlx_get_data_addr");
		ft_exit(all);
	}
	ft_reycasting(all);
	ft_keys(-1, all);
	mlx_hook(all->mlx.winptr, 2, 1, ft_keys, 0);
	//	expose_hook(param);
}

void	initall(t_all *all)
{
	ft_memset(all, 0, sizeof(t_all));
	all->cam.speed = 0.2;
}
