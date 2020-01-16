# include "../include/cub3D.h"

void	initmlx(t_all *all)
{
	if (!(all->mlx.imgptr = mlx_new_image(all->mlx.ptr, all->info.res.x, all->info.res.y)))
	{
		ft_printf("Error\nmlx_new_image");
		ft_exit(all);
	}
	mlx_string_put(all->mlx.ptr, all->mlx.winptr, 400, 300, all->info.c, "bonjour");
	if (!(all->mlx.get_data = (int *)mlx_get_data_addr(all->mlx.imgptr,
					&all->mlx.bits_per_pixel, &all->mlx.size_line, &all->mlx.endian)))
	{
		ft_printf("mlx_get_data_addr");
		ft_exit(all);
	}
}

void	initall(t_all *all)
{
	ft_memset(all, 0, sizeof(t_all));
	all->cam.speed = 0.2;
}
