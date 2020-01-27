/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rendu.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alesanto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 13:33:50 by alesanto          #+#    #+#             */
/*   Updated: 2020/01/27 13:09:48 by alesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/cub3D.h"

void	ft_hl(t_all *all)
{
	while (1)
	{
		if (all->algo.len.x < all->algo.len.y)
		{
			all->algo.len.x += all->algo.delta.x;
			all->cam.map.x += all->algo.dir.x;
			all->algo.NSEO = 0;
		}
		else
		{
			all->algo.len.y += all->algo.delta.y;
			all->cam.map.y += all->algo.dir.y;
			all->algo.NSEO = 1;
		}
		if (all->info.bufmap[all->cam.map.x +
				(all->cam.map.y * all->info.maplen.x)] == '1')
			break;  
	}
	if (all->algo.NSEO == 0)
		all->algo.pDist = (all->cam.map.x - all->cam.raypos.x
				+ (1 - all->algo.dir.x) / 2) / all->cam.rayDir.x;
	else
		all->algo.pDist = (all->cam.map.y - all->cam.raypos.y
				+ (1 - all->algo.dir.y) / 2) / all->cam.rayDir.y;
	all->algo.hauteurLigne = (all->info.res.y / all->algo.pDist);
}

void ft_algo(t_all *all)
{
	if (all->cam.rayDir.x < 0)
	{
		all->algo.dir.x = -1;
		all->algo.len.x = (all->cam.raypos.x - all->cam.map.x) * all->algo.delta.x;
	}
	else
	{
		all->algo.dir.x = 1;
		all->algo.len.x = (all->cam.map.x + 1.0 - all->cam.raypos.x ) * all->algo.delta.x;
	}
	if (all->cam.rayDir.y < 0)
	{
		all->algo.dir.y = -1;
		all->algo.len.y = (all->cam.raypos.y - all->cam.map.y) * all->algo.delta.y;
	}
	else
	{
		all->algo.dir.y = 1;
		all->algo.len.y = (all->cam.map.y + 1.0 - all->cam.raypos.y) * all->algo.delta.y;
	}
}

t_texture 	ft_mettretexture(t_all *all)
{
	if (all->cam.rayDir.x > 0)
	{
		if (all->algo.NSEO)
		{
			if (all->cam.rayDir.y < 0)
				return (all->textureN);
			return (all->textureS);
		}
		return (all->textureE);
	}
	else
	{
		if (all->algo.NSEO)
		{
			if (all->cam.rayDir.y < 0)
				return (all->textureN);
			return (all->textureS);
		}
		return (all->textureW);
	}
}

void	ft_initray(t_all *all, int x)
{
	all->algo.colX = 2 * x / (double)all->info.res.x - 1;
	all->cam.raypos = (t_dcoor){all->cam.pos.x, all->cam.pos.y};
	all->cam.rayDir.x = all->cam.ori.x + all->algo.plane.x * all->algo.colX;
	all->cam.rayDir.y = all->cam.ori.y + all->algo.plane.y * all->algo.colX;
	all->cam.map = (t_coor){(all->cam.raypos.x), (all->cam.raypos.y)};
	all->algo.delta.x = fabs(1 / all->cam.rayDir.x);
	all->algo.delta.y = fabs(1 / all->cam.rayDir.y);
	ft_algo(all);
	ft_hl(all);
	all->algo.drawstart = (-all->algo.hauteurLigne / 2 + all->info.res.y / 2);
	all->algo.drawend = (all->algo.hauteurLigne / 2 + all->info.res.y / 2);
	if (all->algo.drawstart < 0)
		all->algo.drawstart = 0;
	if (all->algo.drawend >= all->info.res.y)
		all->algo.drawend = all->info.res.y - 1;
}

void ft_drawall(t_all *all, int x)
{
	double wallX; 
	int	texX;
	int	texY;
	t_texture img;	

	img = ft_mettretexture(all);
	if (all->algo.NSEO == 1)
		wallX = all->cam.raypos.x + all->algo.pDist * all->cam.rayDir.x;
	else
		wallX = all->cam.raypos.y + all->algo.pDist * all->cam.rayDir.y;
	wallX -= floor(wallX);
	texX = wallX * (double)img.w;
	while (all->algo.drawstart < all->algo.drawend)
	{
		texY = (all->algo.drawstart - all->info.res.y / 2 +
				all->algo.hauteurLigne / 2) * img.h / all->algo.hauteurLigne;
		all->mlx.get_data[x + (int)all->algo.drawstart
			* (all->mlx.size_line / 4)] = img.data[texX + texY * img.w];
		all->algo.drawstart++;
	}
}

void ft_reycasting(t_all *all)
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
		all->spr.distwall[x] = all->algo.pDist;
		x++;
	}
}
