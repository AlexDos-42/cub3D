/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keys.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alesanto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 19:52:22 by alesanto          #+#    #+#             */
/*   Updated: 2020/01/28 14:38:59 by alesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/cub3D.h"

void	ft_moverot(t_all *all)
{
	double	oldorix;
	double	oldplanex;
	double	vitrot;

	vitrot = 0.05;
	if (all->mvt.rot.x)
	{
		oldorix = all->cam.ori.x;
		all->cam.ori.x = all->cam.ori.x * cos(-vitrot) - all->cam.ori.y * sin(-vitrot);
		all->cam.ori.y = oldorix * sin(-vitrot) + all->cam.ori.y * cos(-vitrot);
		oldplanex = all->algo.plane.x;
		all->algo.plane.x = -0.66 * all->cam.ori.y;
		all->algo.plane.y = 0.66 * all->cam.ori.x;
	}
	if (all->mvt.rot.y)
	{
		oldorix = all->cam.ori.x;
		all->cam.ori.x = all->cam.ori.x * cos(vitrot) - all->cam.ori.y * sin(vitrot);
		all->cam.ori.y = oldorix * sin(vitrot) + all->cam.ori.y * cos(vitrot);
		oldplanex = all->algo.plane.x;
		all->algo.plane.x = all->algo.plane.x * cos(vitrot) - all->algo.plane.y * sin(vitrot);
		all->algo.plane.y = oldplanex * sin(vitrot) + all->algo.plane.y * cos(vitrot);
	}
}

int ft_block(t_all *all)
{
		if (all->info.bufmap[(int)all->cam.pos.x + ((int)all->cam.pos.y * all->info.maplen.x)] == '1')
			return (1);
		if (all->info.bufmap[(int)all->cam.pos.x + ((int)all->cam.pos.y * all->info.maplen.x)] == '2')
		{
			if (all->mvt.life <= 1)
			{
			all->mvt.life += 0.05;
			ft_refresh(all);
			}
			return(1);
		}
		return (0);
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
		if (ft_block(all) == 1)
			all->cam.pos.x = posetmpX;
		all->cam.pos.y -= all->algo.plane.y * all->cam.speed;
		if (ft_block(all) == 1)
			all->cam.pos.y = posetmpY;
	}
	if (all->mvt.side.y)
   	{
		all->cam.pos.x +=  all->algo.plane.x * all->cam.speed;
		if (ft_block(all) == 1)
			all->cam.pos.x = posetmpX;
		all->cam.pos.y += all->algo.plane.y * all->cam.speed;
		if (ft_block(all) == 1)
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
		if (ft_block(all) == 1)
			all->cam.pos.x = posetmpX;
		all->cam.pos.y += all->cam.ori.y * all->cam.speed;
		if (ft_block(all) == 1)
			all->cam.pos.y = posetmpY;
	}
	if (all->mvt.up.y)
   	{
		all->cam.pos.x -= all->cam.ori.x * all->cam.speed;
		if (ft_block(all) == 1)
			all->cam.pos.x = posetmpX;
		all->cam.pos.y -= all->cam.ori.y * all->cam.speed;
		if (ft_block(all) == 1)
			all->cam.pos.y = posetmpY;
	}
}

int 	ft_push(int key, t_all *all)
{
	int i;

	i = 0;
	if (key == 48)
	{
		if (all->mvt.hud == 0)
		{
			i = 1;
			all->mvt.hud = 1;
		}
		else
			i = 0;
	}
	if	(all->mvt.hud == 0)
	{
	if (key == 13)
		all->mvt.up.x = 1;
	else if (key == 1)
		all->mvt.up.y = 1;
	if (key == 0)
		all->mvt.side.x = 1;
	else if (key == 2)
		all->mvt.side.y = 1;
	if (key == 12 || key == 123)
		all->mvt.rot.x = 1;
	else if (key == 14 || key == 124)
		all->mvt.rot.y = 1;
	if (key == 46)
	{
		if (all->mvt.msc == 0)
		{
			system("afplay objet/simpson.mp3&");
			all->mvt.msc = 1;
		ft_refresh(all);
		}
	}
	if (key == 40)
	{
		if (all->mvt.msc == 1)
		{
			system("pkill afplay");
			all->mvt.msc = 0;
			ft_refresh(all);
		}
	}
	if (key == 32)
	{
		if (all->mvt.life <= 1)
		{
			all->mvt.life += 0.25;
			ft_refresh(all);
			all->mvt.msc = 0;
		}
	}
	else if (key == 34)
	{
		if (all->mvt.life != 0)
		{
		system("afplay objet/donuts.mp3&");
		all->mvt.life = 0; 
		ft_refresh(all);
		}
	}
	}
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
	else if (key == 12 || key == 123)
		all->mvt.rot.x = 0;
	else if (key == 14 || key == 124)
		all->mvt.rot.y = 0;
	else if (key == 53)
	{
		ft_printf(ERROR_GO);
		ft_exit(all);
	}
	return (0);
}

int	ft_keys(t_all *all)
{
	double	tmp;

	tmp = all->cam.pos.x + all->cam.pos.y + all->cam.ori.x + all->cam.ori.y + all->algo.plane.x;
	if (all->mvt.up.x == 1 || all->mvt.up.y == 1)
		ft_moveup(all);
	if (all->mvt.side.x == 1 || all->mvt.side.y == 1)
		ft_moveside(all);
	if (all->mvt.rot.x  == 1|| all->mvt.rot.y == 1)
		ft_moverot(all);
	if (all->mvt.hud == 1)
	{
		ft_hud(all);
		all->mvt.hud = 0;
	}
	if (tmp != (all->cam.pos.x + all->cam.pos.y + all->cam.ori.x + all->cam.ori.y + all->algo.plane.x))
		ft_refresh(all);

	return (0);
}
