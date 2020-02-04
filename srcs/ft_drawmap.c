/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_drawmap.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alesanto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 19:39:46 by alesanto          #+#    #+#             */
/*   Updated: 2020/01/30 18:00:11 by alesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

t_texture		ft_mettretexture(t_all *all)
{
	if (all->cam.raydir.x > 0)
	{
		if (all->algo.nseo)
		{
			if (all->cam.raydir.y < 0)
				return (all->texturen);
			return (all->textures);
		}
		return (all->texturee);
	}
	else
	{
		if (all->algo.nseo)
		{
			if (all->cam.raydir.y < 0)
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
	if (all->algo.nseo == 1)
		wallx = all->cam.raypos.x + all->algo.pdist * all->cam.raydir.x;
	else
		wallx = all->cam.raypos.y + all->algo.pdist * all->cam.raydir.y;
	wallx -= floor(wallx);
	texx = wallx * (double)img.w;
	while (all->algo.drawstart < all->algo.drawend)
	{
		texy = (all->algo.drawstart - all->info.res.y / 2 +
				all->algo.hauteurligne / 2) * img.h / all->algo.hauteurligne;
		all->mlx.get_data[x + (int)all->algo.drawstart
			* (all->mlx.size_line / 4)] = img.data[texx + texy * img.w];
		all->algo.drawstart++;
	}
}
