/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alesanto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 20:06:07 by alesanto          #+#    #+#             */
/*   Updated: 2020/01/14 20:20:17 by alesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/cub3D.h"

int		main(int argc, char **argv)
{
	t_all	all;

	if (argc < 2 || argc > 3)
	{
		printf(ERROR_ARGC, argc);
		ft_exit(&all);
	}
	initall(&all);
	ft_parsing(argv, &all);
	if ((all->cam.isit != 1))
	{
		ft_printf(ERROR_PLAYER, all.cam.isit);
		ft_exit(all);
	}
	initmlx(&all);
	mlx_loop(all.mlx.ptr);
	return (0);
}
