/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alesanto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 14:51:15 by alesanto          #+#    #+#             */
/*   Updated: 2020/01/29 17:32:13 by alesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	initmlx(all);
	ft_reycasting(all);
	ft_sprites(all);
	mlx_put_image_to_window(all->mlx.ptr, all->mlx.winptr, all->mlx.imgptr, 0, 0);
 	load_textures(all);
	ft_draw_hand(all);
	load_hudtex(all);
	ft_draw_hud(all);
	draw_vie(all);
	mlx_destroy_image(all->mlx.ptr, all->mlx.imgptr);
}

void	initall(t_all *all, char **argv)
{
	ft_memset(all, 0, sizeof(t_all));
	all->cam.speed = 0.333;
	ft_parsing(argv, all);
	initwindow(all);
	ft_textures(all);
	ft_refresh(all);
}
