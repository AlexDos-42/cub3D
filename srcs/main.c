/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alesanto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 20:06:07 by alesanto          #+#    #+#             */
/*   Updated: 2020/01/28 17:46:44 by alesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/cub3D.h"

void ft_cub(*argv)
{
	len = ft_strlen(argv[1]);
	if (!(ft_strcmp(argv[1] + len - 4, ".cub"))
	{
		ft_printf("Invalide map file : file extention isn't .cub");
		ft_exit(&all);
	}
}

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
	ft_cub(argv[1]);
	initall(&all, argv);
	mlx_do_key_autorepeatoff(all.mlx.ptr);	
	mlx_hook(all.mlx.winptr, 2, (1L << 0), &ft_push, &all);
	mlx_hook(all.mlx.winptr, 3, (1L << 1), &ft_depush, &all);
	mlx_hook(all.mlx.winptr, 17, 0, &ft_redcross, &all);
	mlx_loop_hook(all.mlx.ptr, &ft_keys, &all);	
	mlx_loop(all.mlx.ptr);
	return (0);
}
