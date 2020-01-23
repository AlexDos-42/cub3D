/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alesanto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 20:06:07 by alesanto          #+#    #+#             */
/*   Updated: 2020/01/23 16:14:59 by alesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/cub3D.h"

int		ft_redcross(t_all *all)
{
	ft_printf("GAME OVER");
	ft_exit(all);
	return (0);
}

int		main(int argc, char **argv)
{
	t_all	all;

	if (argc < 2 || argc > 3)
	{
		ft_printf(ERROR_ARGC, argc);
		ft_exit(&all);
	}
	initall(&all, argv);
	printf("main1\n");
	mlx_do_key_autorepeatoff(all.mlx.ptr);	
	printf("main2\n");
	mlx_hook(all.mlx.winptr, 2, (1L << 0), &ft_push, &all);
	printf("main3\n");
	mlx_hook(all.mlx.winptr, 3, (1L << 1), &ft_depush, &all);
	printf("main4\n");
	mlx_hook(all.mlx.winptr, 17, 0, &ft_redcross, &all);
	printf("main5\n");
	mlx_loop_hook(all.mlx.ptr, &ft_keys, &all);
	printf("main6\n");
	mlx_loop(all.mlx.ptr);	
	printf("main7\n");
	return (0);
}
