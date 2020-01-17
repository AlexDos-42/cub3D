/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keys.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alesanto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 19:52:22 by alesanto          #+#    #+#             */
/*   Updated: 2020/01/17 21:51:53 by alesanto         ###   ########.fr       */
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

void	ft_moverot(t_all *all)
{
	double	oldorix;
	double	oldplanex;

	if (all->mvt.rot.x)
	{
		oldorix = all->cam.ori.x;
		all->cam.ori.x = all->cam.ori.x * cos(-0.3) - all->cam.ori.y * sin(-0.3);
		all->cam.ori.y = oldorix * sin(-0.3) + all->cam.ori.y * cos(-0.3);
		oldplanex = all->algo.plane.x;
		all->algo.plane.x = all->algo.plane.x * cos(-0.3) - all->algo.plane.y * sin(-0.3);
		all->algo.plane.y = oldplanex * sin(-0.3) + all->algo.plane.y * cos(-0.3);
	}
	if (all->mvt.rot.y)
	{
		oldorix = all->cam.ori.x;
		all->cam.ori.x = all->cam.ori.x * cos(0.3) - all->cam.ori.y * sin(0.3);
		all->cam.ori.y = oldorix * sin(0.3) + all->cam.ori.y * cos(0.3);
		oldplanex = all->algo.plane.x;
		all->algo.plane.x = all->algo.plane.x * cos(0.3) - all->algo.plane.x * sin(0.3);
		all->algo.plane.y = oldplanex * sin(0.3) + all->algo.plane.y * cos(0.3);
	}
}

void	ft_moveside(t_all *all)
{
	double posetmpX;
	double posetmpY;
	posetmpX = all->cam.pos.x;
	posetmpY = all->cam.pos.y;	

	if (all->mvt.side.x)
   	{
		all->cam.pos.x -= all->algo.plane.x * all->cam.speed;
		if (all->info.bufmap[(int)all->cam.pos.x + ((int)all->cam.pos.y * all->info.maplen.x)] == '1')
			all->cam.pos.x = posetmpX;
		all->cam.pos.y -= all->algo.plane.y * all->cam.speed;
		if (all->info.bufmap[(int)all->cam.pos.x + ((int)all->cam.pos.y * all->info.maplen.x)] == '1')
			all->cam.pos.y = posetmpY;
	}
	if (all->mvt.side.y)
   	{
		all->cam.pos.x +=  all->algo.plane.x * all->cam.speed;
		if (all->info.bufmap[(int)all->cam.pos.x + ((int)all->cam.pos.y * all->info.maplen.x)] == 'i')
			all->cam.pos.x = posetmpX;
		all->cam.pos.y += all->algo.plane.y * all->cam.speed;
		if (all->info.bufmap[(int)all->cam.pos.x + ((int)all->cam.pos.y * all->info.maplen.x)] == '1')
			all->cam.pos.y = posetmpY;
	}
}
void ft_moveup(t_all *all)
{
	double posetmpX;
	double posetmpY;
	posetmpX = all->cam.pos.x;
	posetmpY = all->cam.pos.y;	

	if (all->mvt.up.x)
   	{
		all->cam.pos.x += all->cam.ori.x * all->cam.speed;
		if (all->info.bufmap[(int)all->cam.pos.x + ((int)all->cam.pos.y * all->info.maplen.x)] == '1')
			all->cam.pos.x = posetmpX;
		all->cam.pos.y += all->cam.ori.y * all->cam.speed;
		if (all->info.bufmap[(int)all->cam.pos.x + ((int)all->cam.pos.y * all->info.maplen.x)] == '1')
			all->cam.pos.y = posetmpY;
	}
	if (all->mvt.up.y)
   	{
		all->cam.pos.x -= all->cam.ori.x * all->cam.speed;
		if (all->info.bufmap[(int)all->cam.pos.x + ((int)all->cam.pos.y * all->info.maplen.x)] == '1')
			all->cam.pos.x = posetmpX;
		all->cam.pos.y -= all->cam.ori.y * all->cam.speed;
		if (all->info.bufmap[(int)all->cam.pos.x + ((int)all->cam.pos.y * all->info.maplen.x)] == '1')
			all->cam.pos.y = posetmpY;
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
	if (key == 12)
		all->mvt.rot.x = 1;
	else if (key == 14 )
		all->mvt.rot.y = 1;
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
	else if (key == 12)
		all->mvt.rot.x = 0;
	else if (key == 14)
		all->mvt.rot.y = 0;
//	else if (key == )
//		return (exit_game(game, EXIT_SUCCESS));
	return (0);
}

int	ft_keys(t_all *all)
{
	printf("all->mvt.up.x %d\n", all->mvt.up.x);
	double	tmp;
	
	tmp = all->cam.pos.x + all->cam.pos.y;
	printf("tmp %f\n",tmp);
	if (all->mvt.up.x == 1 || all->mvt.up.y == 1)
		ft_moveup(all);
	if (all->mvt.side.x == 1 || all->mvt.side.y == 1)
		ft_moveside(all);
		printf("testkeys1\n");
	if (all->mvt.rot.x  == 1|| all->mvt.rot.y == 1)
		ft_moverot(all);
//	else if (key == 123 || key == 124)
//		ft_rotate(key, all);
//	else if (key == 53)
//		game_over();
	printf("tmp %f\n",tmp);
	if (tmp != (all->cam.pos.x + all->cam.pos.y))
	{
		printf("is tmp !=");
		initmlx(all);
		ft_reycasting(all);
	}
	return (0);
}
