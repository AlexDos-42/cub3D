/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alesanto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 20:06:07 by alesanto          #+#    #+#             */
/*   Updated: 2020/01/17 13:28:49 by alesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/cub3D.h"

int		main(int argc, char **argv)
{
	t_all	all;

	if (argc < 2 || argc > 3)
	{
		ft_printf(ERROR_ARGC, argc);
		ft_exit(&all);
	}
	initall(&all);
	ft_parsing(argv, &all);
	if ((all.cam.isit != 1))
	{
		ft_printf(ERROR_PLAYER, all.cam.isit);
		ft_exit(&all);
	}
	 if (!(all.mlx.ptr = mlx_init()))
	{
 		ft_printf("Error\nmlx_init");
		ft_exit(&all);
   	}
	if (!(all.mlx.winptr = mlx_new_window(all.mlx.ptr, all.info.res.x, all.info.res.y, "cub3D")))
	{
		ft_printf("Error\nmlx_init");
		ft_exit(&all);
	}
	initmlx(&all);
	ft_reycasting(&all);
	ft_keys(&all);
	mlx_do_key_autorepeatoff(all.mlx.ptr);	
	mlx_hook(all.mlx.winptr, 2, (1L << 0), &ft_push, &all);
	mlx_hook(all.mlx.winptr, 3, (1L << 1), &ft_depush, &all);
	mlx_loop_hook(all.mlx.ptr, &ft_keys, &all);
	mlx_loop(all.mlx.ptr);	
	return (0);
}
