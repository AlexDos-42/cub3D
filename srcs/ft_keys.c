/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keys.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alesanto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 19:52:22 by alesanto          #+#    #+#             */
/*   Updated: 2020/01/16 18:03:59 by alesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/cub3D.h"


static void	set_ceil(t_all *all)
{
	int *image;
	int i;
	int j;

	image = all->mlx.get_data;
	i = 0;
	while (i < all->info.res.y / 2)
	{
		j = 0;
		while (j < all->info.res.x)
		{
			image[j + i * all->mlx.size_line] = 0x006666;
			j++;
		}
		i++;
	}
}

static void	set_floor(t_all *all)
{
	int *image;
	int i;
	int j;

	image = all->mlx.get_data;
	i = all->info.res.y / 2;
	while (i < all->info.res.y)
	{
		j = 0;
		while (j < all->info.res.x)
		{
			image[j + i * all->mlx.size_line] = 0x006666;
			j++;
		}
		i++;
	}
}

void		reset_image(t_all *all)
{
	set_floor(all);
	set_ceil(all);
}



void	ft_moveside(t_all *all)
{
	if (all->mvt.side.x)
   	{
		if (all->info.bufmap[(int)(all->cam.map.x + (int)(all->cam.ori.x * all->cam.speed))
				+ (all->cam.map.y * all->info.maplen.x)] == 0)
			all->cam.pos.x += all->cam.ori.x * all->cam.speed;
		if (all->info.bufmap[all->cam.map.x + ((int)(all->cam.map.y
				+ all->cam.ori.y * all->cam.speed) * all->info.maplen.x)] == 0)
			all->cam.pos.y += all->cam.ori.y * all->cam.speed;
	}
	if (all->mvt.side.y)
   	{
		if (all->info.bufmap[(int)(all->cam.map.x - (int)(all->cam.ori.x * all->cam.speed))
				+ (all->cam.map.y * all->info.maplen.x)] == 0)
			all->cam.pos.x -= all->cam.ori.x * all->cam.speed;
		if (all->info.bufmap[all->cam.map.x + ((int)(all->cam.map.y
				- all->cam.ori.y * all->cam.speed) * all->info.maplen.x)] == 0)
			all->cam.pos.y -= all->cam.ori.y * all->cam.speed;
	}
}
void ft_moveup(t_all *all)
{
	printf("up\n");
	if (all->mvt.up.x)
   	{
	printf("all->cam.pos.y %f\n", all->cam.pos.y);
	if (all->info.bufmap[(int)(all->cam.map.x + (int)(all->cam.ori.x * all->cam.speed))
			+ (all->cam.map.y * all->info.maplen.x)] == 0)
			all->cam.pos.x += all->cam.ori.x * all->cam.speed;
	if (all->info.bufmap[all->cam.map.x + ((int)(all->cam.map.y
				+ all->cam.ori.y * all->cam.speed) * all->info.maplen.x)] == 0)
			all->cam.pos.y += all->cam.ori.y * all->cam.speed;
	printf("all->cam.pos.y %f\n", all->cam.pos.y);
	}
	if (all->mvt.up.y)
   	{
		if (all->info.bufmap[(int)(all->cam.map.x - (int)(all->cam.ori.x * all->cam.speed))
				+ (all->cam.map.y * all->info.maplen.x)] == 0)
			all->cam.pos.x -= all->cam.ori.x * all->cam.speed;
		if (all->info.bufmap[all->cam.map.x + ((int)(all->cam.map.y
				- all->cam.ori.y * all->cam.speed) * all->info.maplen.x)] == 0)
			all->cam.pos.y -= all->cam.ori.y * all->cam.speed;
	}
	return ;
}

int 	ft_push(int key, t_all *all)
{
	printf("push\n");
	if (key == 13)
		all->mvt.up.x = 1;
	else if (key == 1)
		all->mvt.up.y = 1;
	if (key == 0)
		all->mvt.side.x = 1;
	else if (key == 2)
		all->mvt.side.y = 1;
//	if (key == )
//		all->mvt.rot.x = 1;
//	else if (key ==  )
//		all->mvt.rot.y = 1;
	return (0);
}

int	 ft_depush(int key, t_all *all)
{
	if (key == 13)
		all->mvt.up.x = 0;
	else if (key == 1)
		all->mvt.up.y = 0;
	if (key == 0)
		all->mvt.side.x = 0;
	else if (key == 2)
		all->mvt.side.y = 0;
//	else if (key == )
//		all->mvt.rot.x = 0;
//	else if (key == )
//		all->mvt.rot.y = 0;
//	else if (key == )
//		return (exit_game(game, EXIT_SUCCESS));
	return (0);
}

int	ft_keys(t_all *all)
{
	printf("testkeys\n");
	printf("all->mvt.up.x %d\n", all->mvt.up.x);
	if (all->mvt.up.x == 1 || all->mvt.up.y == 1)
		ft_moveup(all);
	else if (all->mvt.side.x == 1 || all->mvt.side.y == 1)
		ft_moveside(all);
	printf("testkeys1\n");
//	if (all->mvt.side.x || all->mvt.side.y)
//		ft_moveside(key, all);
//	if (all->mvt.rot.x || all->mvt.rot.y)
//		ft_moverot(key, all);
//	else if (key == 123 || key == 124)
//		ft_rotate(key, all);
//	else if (key == 53)
//		game_over();
//	reset_image(all);
	initmlx(all);
	ft_reycasting(all);
	printf("testkeys3\n");
	return (0);
}
