/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_push.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alesanto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 20:08:44 by alesanto          #+#    #+#             */
/*   Updated: 2020/01/29 20:08:47 by alesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void		ft_pushlife(int key, t_all *all)
{
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

void		ft_pushmsc(int key, t_all *all)
{
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
}

int			ft_push(int key, t_all *all)
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
	if (key == 257)
		all->cam.speed = 0.6;
	ft_pushmsc(key, all);
	ft_pushlife(key, all);
	return (0);
}

int			ft_depush(int key, t_all *all)
{
	if (key == 13)
		all->mvt.up.x = 0;
	else if (key == 1)
		all->mvt.up.y = 0;
	if (key == 0)
		all->mvt.side.x = 0;
	else if (key == 2)
		all->mvt.side.y = 0;
	if (key == 12 || key == 123)
		all->mvt.rot.x = 0;
	else if (key == 14 || key == 124)
		all->mvt.rot.y = 0;
	if (key == 53)
	{
		ft_printf(ERROR_GO);
		ft_exit(all);
	}
	if (key == 257)
		all->cam.speed = 0.333;
	return (0);
}
