/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_drawmap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alesanto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 19:39:46 by alesanto          #+#    #+#             */
/*   Updated: 2020/01/29 23:07:30 by alesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

t_texture		ft_mettretexture(t_all *all)
{
	if (all->cam.rayDir.x > 0)
	{
		if (all->algo.NSEO)
		{
			if (all->cam.rayDir.y < 0)
				return (all->texturen);
			return (all->textures);
		}
		return (all->texturee);
	}
	else
	{
		if (all->algo.NSEO)
		{
			if (all->cam.rayDir.y < 0)
				return (all->texturen);
			return (all->textures);
		}
		return (all->texturew);
	}
}

void			ft_drawall(t_all *all, int x)
{
	double		wallx;
	int			texx;
	int			texy;
	t_texture	img;

	img = ft_mettretexture(all);
	if (all->algo.NSEO == 1)
		wallx = all->cam.raypos.x + all->algo.pDist * all->cam.rayDir.x;
	else
		wallx = all->cam.raypos.y + all->algo.pDist * all->cam.rayDir.y;
	wallx -= floor(wallx);
	texx = wallx * (double)img.w;
	while (all->algo.drawstart < all->algo.drawend)
	{
		texy = (all->algo.drawstart - all->info.res.y / 2 +
				all->algo.hauteurLigne / 2) * img.h / all->algo.hauteurLigne;
		all->mlx.get_data[x + (int)all->algo.drawstart
			* (all->mlx.size_line / 4)] = img.data[texx + texy * img.w];
		all->algo.drawstart++;
	}
}
