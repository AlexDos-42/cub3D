/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keys.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alesanto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 19:52:22 by alesanto          #+#    #+#             */
/*   Updated: 2020/01/14 21:12:06 by alesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/cub3D.h"

void ft_move(int key, t_all *all)
{
		printf("all->cam.speed %f\n", all->cam.speed);
	if (key == 13)
   	{
		printf("all->cam.speed %f\n", all->cam.speed);
		if (all->info.bufmap[(int)(all->cam.map.x + (int)(all->cam.ori.x * all->cam.speed))
				+ (all->cam.map.y * all->info.maplen.x)] == 0)
			all->cam.pos.x += all->cam.ori.x * all->cam.speed;
		if (all->info.bufmap[all->cam.map.x + ((int)(all->cam.map.y
				+ all->cam.ori.y * all->cam.speed) * all->info.maplen.x)] == 0)
			all->cam.pos.y += all->cam.ori.y * all->cam.speed;
	}
	if (key == 1)
   	{
		if (all->info.bufmap[(int)(all->cam.map.x - (int)(all->cam.ori.x * all->cam.speed))
				+ (all->cam.map.y * all->info.maplen.x)] == 0)
			all->cam.pos.x -= all->cam.ori.x * all->cam.speed;
		if (all->info.bufmap[all->cam.map.x + ((int)(all->cam.map.y
				- all->cam.ori.y * all->cam.speed) * all->info.maplen.x)] == 0)
			all->cam.pos.y -= all->cam.ori.y * all->cam.speed;
	}
}

int	ft_keys(int key, t_all *all)
{
		printf("all->cam.speed %f\n", all->cam.speed);
		printf("key %d\n", key);
		
	if (key == 13 || key == 1 || key == 0 || key == 2)
		ft_move(key, all);
//	else if (key == 123 || key == 124)
//		ft_rotate(key, all);
//	else if (key == 53)
//		game_over();
//	reset_image();
//	cast_all();
//	mlx_put_image_to_window(g_window.mlx_ptr,
//			g_window.win_ptr,
//			g_window.image.ptr,
//			0, 0);
	return (0);
}
