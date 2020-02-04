/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alesanto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 14:51:15 by alesanto          #+#    #+#             */
/*   Updated: 2020/02/04 21:27:59 by alesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void		initmlx(t_all *all)
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
		ft_printf("Error\nmlx_get_data_addr");
		ft_exit(all);
	}
}

void		initwindow(t_all *all, char **argv)
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
	ft_sprites(all);
	ft_textures(all);
	if (argv[2] && !ft_strncmp(argv[2], "--save", 10))
		ft_bmpinit(all);
	else if (argv[2])
	{
		ft_printf("Error\nyou're second argument isn't --save");
		ft_exit(all);
	}
	if (!(all->mlx.winptr = mlx_new_window(all->mlx.ptr,
			all->info.res.x, all->info.res.y, "cub3D")))
	{
		ft_printf("Error\nmlx_init");
		ft_exit(all);
	}
}

void		ft_refresh(t_all *all)
{
	initmlx(all);
	if (!(all->spr.distwall = ft_calloc(sizeof(double*), all->info.res.x)))
	{
		ft_printf(ERROR_MALLOC, "all->spr.distwall");
		ft_exit(all);
	}
	ft_reycasting(all);
	init_sprites(all);
	mlx_put_image_to_window(all->mlx.ptr,
		all->mlx.winptr, all->mlx.imgptr, 0, 0);
	load_textures(all);
	ft_draw_hand(all);
	load_hudtex(all);
	ft_draw_hud(all);
	draw_vie(all);
	mlx_destroy_image(all->mlx.ptr, all->mlx.imgptr);
}

void		initall(t_all *all, char **argv)
{
	ft_memset(all, 0, sizeof(t_all));
	all->cam.speed = 0.15;
	all->cam.vitrot = 0.1;
	ft_parsing(argv, all);
	if (all->info.res.x > 2560)
		all->info.res.x = 2560;
	else if (all->info.res.x < 100)
		all->info.res.x = 100;
	if (all->info.res.y > 1440)
		all->info.res.y = 1440;
	else if (all->info.res.y < 100)
		all->info.res.y = 100;
	initwindow(all, argv);
	ft_refresh(all);
}
