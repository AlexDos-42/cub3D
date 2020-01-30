/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rendu.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alesanto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 13:33:50 by alesanto          #+#    #+#             */
/*   Updated: 2020/01/30 17:59:40 by alesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void		ft_hl(t_all *all)
{
	while (1)
	{
		if (all->algo.len.x < all->algo.len.y)
		{
			all->algo.len.x += all->algo.delta.x;
			all->cam.map.x += all->algo.dir.x;
			all->algo.nseo = 0;
		}
		else
		{
			all->algo.len.y += all->algo.delta.y;
			all->cam.map.y += all->algo.dir.y;
			all->algo.nseo = 1;
		}
		if (all->info.bufmap[all->cam.map.x +
				(all->cam.map.y * all->info.maplen.x)] == '1')
			break ;
	}
	if (all->algo.nseo == 0)
		all->algo.pdist = (all->cam.map.x - all->cam.raypos.x
				+ (1 - all->algo.dir.x) / 2) / all->cam.raydir.x;
	else
		all->algo.pdist = (all->cam.map.y - all->cam.raypos.y
				+ (1 - all->algo.dir.y) / 2) / all->cam.raydir.y;
	all->algo.hauteurligne = (all->info.res.y / all->algo.pdist);
}

void		ft_algo(t_all *all)
{
	if (all->cam.raydir.x < 0)
	{
		all->algo.dir.x = -1;
		all->algo.len.x = (all->cam.raypos.x
			- all->cam.map.x) * all->algo.delta.x;
	}
	else
	{
		all->algo.dir.x = 1;
		all->algo.len.x = (all->cam.map.x + 1.0
			- all->cam.raypos.x) * all->algo.delta.x;
	}
	if (all->cam.raydir.y < 0)
	{
		all->algo.dir.y = -1;
		all->algo.len.y = (all->cam.raypos.y
			- all->cam.map.y) * all->algo.delta.y;
	}
	else
	{
		all->algo.dir.y = 1;
		all->algo.len.y = (all->cam.map.y + 1.0
			- all->cam.raypos.y) * all->algo.delta.y;
	}
}

void		ft_initray(t_all *all, int x)
{
	all->algo.colx = 2 * x / (double)all->info.res.x - 1;
	all->cam.raypos = (t_dcoor){all->cam.pos.x, all->cam.pos.y};
	all->cam.raydir.x = all->cam.ori.x + all->algo.plane.x * all->algo.colx;
	all->cam.raydir.y = all->cam.ori.y + all->algo.plane.y * all->algo.colx;
	all->cam.map = (t_coor){(all->cam.raypos.x), (all->cam.raypos.y)};
	all->algo.delta.x = fabs(1 / all->cam.raydir.x);
	all->algo.delta.y = fabs(1 / all->cam.raydir.y);
	ft_algo(all);
	ft_hl(all);
	all->algo.drawstart = (-all->algo.hauteurligne / 2 + all->info.res.y / 2);
	all->algo.drawend = (all->algo.hauteurligne / 2 + all->info.res.y / 2);
	if (all->algo.drawstart < 0)
		all->algo.drawstart = 0;
	if (all->algo.drawend >= all->info.res.y)
		all->algo.drawend = all->info.res.y;
}

void		ft_reycasting(t_all *all)
{
	int x;
	int y;

	x = 0;
	while (x < all->info.res.x)
	{
		ft_initray(all, x);
		ft_drawall(all, x);
		y = all->algo.drawend;
		while (y < all->info.res.y)
		{
			all->mlx.get_data[x + y *
				(all->mlx.size_line / 4)] = all->info.f;
			all->mlx.get_data[x + (all->info.res.y - y - 1)
				* (all->mlx.size_line / 4)] = all->info.c;
			y++;
		}
		all->spr.distwall[x] = all->algo.pdist;
		x++;
	}
}
