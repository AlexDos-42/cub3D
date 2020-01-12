/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rendu.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alesanto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 13:33:50 by alesanto          #+#    #+#             */
/*   Updated: 2020/01/12 14:17:52 by alesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/cub3D.h"

void ft_reycasting(t_all *all)
{
	int x;
	int y;

	x = 0;
	while (x <= all->info.res.x)
	{
		all->algo.hit = 0;
		all->algo.colX = (2 * x / all->info.maplen.x) - 1;
		all->cam.pos.x = all->cam.raypos.x;
		all->cam.pos.y = all->cam.raypos.y;
		all->cam.rayDir.x = all->cam.ori.x + all->algo.plane.x * all->algo.colX;
		all->cam.rayDir.y = all->cam.ori.y + all->algo.plane.y * all->algo.colX;
		all->cam.map.x = all->cam.raypos.x;
		all->cam.map.y = all->cam.raypos.y;
		all->algo.delta.x = sqrt(1 + (all->cam.rayDir.x * all->cam.rayDir.y) / (all->cam.rayDir.x * all->cam.rayDir.y));
		all->algo.delta.y = sqrt(1 + (all->cam.rayDir.y * all->cam.rayDir.x) / (all->cam.rayDir.y * all->cam.rayDir.x));
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
		while (all->algo.hit == 0)
	   	{
			if (all->algo.len.x < all->algo.len.y)
		   	{
				all->algo.len.x += all->algo.delta.x;// agrandis le rayon
				all->cam.map.x += all->algo.dir.x;// prochaine case ou case précédente sur X
				all->algo.NSEO = 0;// orientation du mur
			}
	  	 	else
	  	 	{
				all->algo.len.y += all->algo.delta.y;// agrandis le rayon
				all->cam.map.y += all->algo.dir.y;// prochaine case ou case précédente sur Y
				all->algo.NSEO = 1;// orientation du mur
			}
 				// si le rayon rencontre un mur
			if (all->info.bufmap[all->cam.map.y + (all->cam.map.x * all->info.maplen.x)]>0)
				all->algo.hit = 1; // stoppe la boucle 
		}
		if (all->algo.NSEO == 0)
			all->algo.pDist = fabs((all->cam.map.x - all->cam.raypos.x + (1 - all->algo.dir.x) / 2) / all->cam.rayDir.x);
		else
			all->algo.pDist = fabs((all->cam.map.y - all->cam.raypos.y + (1 - all->algo.dir.y) / 2) / all->cam.rayDir.y);
		all->algo.hauteurLigne = fabs(all->info.res.y / all->algo.pDist);
		all->algo.drawstart = (int)(-all->algo.hauteurLigne / 2 + all->info.res.y / 2);
		all->algo.drawend = (int)(all->algo.hauteurLigne / 2 + all->info.res.y / 2);
		if (all->algo.drawstart < 0)
			all->algo.drawstart = 0;
		if (all->algo.drawend >= all->info.res.y)
			all->algo.drawend = all->info.res.y - 1;
		y = all->algo.drawstart;
		printf("y%d\n lenx%d\n", y, all->info.res.x);
		while (y < all->algo.drawend)
	   	{
		 	int color = 0xff0000;// couleur du pixel pour un mur Nord/Sud
			if (all->algo.NSEO == 1)
				color = 0x0000ff;// couleur du pixel pour un mur Est/Ouest
		mlx_pixel_put( all->mlx.ptr, all->mlx.winptr, x, y, color);
			y++;// incrémente la position Y du prochain pixel à tracer
		}
		if (all->algo.drawend < 0) 
			all->algo.drawend = all->info.res.y;
		y = all->algo.drawend;
		while (y < all->info.res.y)
		{  
			mlx_pixel_put(all->mlx.ptr, all->mlx.winptr, x, y, 0x006666);
			mlx_pixel_put(all->mlx.ptr, all->mlx.winptr, x, all->info.res.y - y - 1, 0x006666);
			y++;
		}
		x++;
	}
}
