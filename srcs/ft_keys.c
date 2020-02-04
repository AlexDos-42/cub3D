/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_keys.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alesanto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/14 19:52:22 by alesanto          #+#    #+#             */
/*   Updated: 2020/01/29 20:06:34 by alesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void		ft_moverot(t_all *all)
{
	double	oldorix;
	double	oldplanex;

	if (all->mvt.rot.x)
	{
		oldorix = all->cam.ori.x;
		all->cam.ori.x = all->cam.ori.x * cos(-all->cam.vitrot)
			- all->cam.ori.y * sin(-all->cam.vitrot);
		all->cam.ori.y = oldorix * sin(-all->cam.vitrot) +
			all->cam.ori.y * cos(-all->cam.vitrot);
		oldplanex = all->algo.plane.x;
		all->algo.plane.x = -0.66 * all->cam.ori.y;
		all->algo.plane.y = 0.66 * all->cam.ori.x;
	}
	if (all->mvt.rot.y)
	{
		oldorix = all->cam.ori.x;
		all->cam.ori.x = all->cam.ori.x * cos(all->cam.vitrot)
			- all->cam.ori.y * sin(all->cam.vitrot);
		all->cam.ori.y = oldorix * sin(all->cam.vitrot)
			+ all->cam.ori.y * cos(all->cam.vitrot);
		oldplanex = all->algo.plane.x;
		all->algo.plane.x = -0.66 * all->cam.ori.y;
		all->algo.plane.y = 0.66 * all->cam.ori.x;
	}
}

int			ft_block(t_all *all)
{
	if (all->info.bufmap[(int)all->cam.pos.x
		+ ((int)all->cam.pos.y * all->info.maplen.x)] == '1')
		return (1);
	if (all->info.bufmap[(int)all->cam.pos.x
		+ ((int)all->cam.pos.y * all->info.maplen.x)] == '2')
	{
		if (all->mvt.life <= 1)
		{
			all->mvt.life += 0.05;
			ft_refresh(all);
		}
		return (1);
	}
	return (0);
}

void		ft_moveside(t_all *all)
{
	double posetmpx;
	double posetmpy;

	posetmpx = all->cam.pos.x;
	posetmpy = all->cam.pos.y;
	if (all->mvt.side.x)
	{
		all->cam.pos.x -= all->algo.plane.x * all->cam.speed;
		if (ft_block(all) == 1)
			all->cam.pos.x = posetmpx;
		all->cam.pos.y -= all->algo.plane.y * all->cam.speed;
		if (ft_block(all) == 1)
			all->cam.pos.y = posetmpy;
	}
	if (all->mvt.side.y)
	{
		all->cam.pos.x += all->algo.plane.x * all->cam.speed;
		if (ft_block(all) == 1)
			all->cam.pos.x = posetmpx;
		all->cam.pos.y += all->algo.plane.y * all->cam.speed;
		if (ft_block(all) == 1)
			all->cam.pos.y = posetmpy;
	}
}

void		ft_moveup(t_all *all)
{
	double posetmpx;
	double posetmpy;

	posetmpx = all->cam.pos.x;
	posetmpy = all->cam.pos.y;
	if (all->mvt.up.x)
	{
		all->cam.pos.x += all->cam.ori.x * all->cam.speed;
		if (ft_block(all) == 1)
			all->cam.pos.x = posetmpx;
		all->cam.pos.y += all->cam.ori.y * all->cam.speed;
		if (ft_block(all) == 1)
			all->cam.pos.y = posetmpy;
	}
	if (all->mvt.up.y)
	{
		all->cam.pos.x -= all->cam.ori.x * all->cam.speed;
		if (ft_block(all) == 1)
			all->cam.pos.x = posetmpx;
		all->cam.pos.y -= all->cam.ori.y * all->cam.speed;
		if (ft_block(all) == 1)
			all->cam.pos.y = posetmpy;
	}
}

int			ft_keys(t_all *all)
{
	double	tmp;

	tmp = all->cam.pos.x + all->cam.pos.y +
		all->cam.ori.x + all->cam.ori.y + all->algo.plane.x;
	if (all->mvt.up.x == 1 || all->mvt.up.y == 1)
		ft_moveup(all);
	if (all->mvt.side.x == 1 || all->mvt.side.y == 1)
		ft_moveside(all);
	if (all->mvt.rot.x == 1 || all->mvt.rot.y == 1)
		ft_moverot(all);
	if (tmp != (all->cam.pos.x + all->cam.pos.y
		+ all->cam.ori.x + all->cam.ori.y + all->algo.plane.x))
		ft_refresh(all);
	return (0);
}
