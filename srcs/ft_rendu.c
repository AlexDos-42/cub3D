/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rendu.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alesanto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 13:33:50 by alesanto          #+#    #+#             */
/*   Updated: 2020/01/11 20:28:16 by alesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/cub3D.h"

void ft_reycasting(t_all *all)
{
	int x;
	int y;

	x = 0;
	while (x <= all->info.resx)
	{
		y = 0;
		all->algo.hit = 0;
		all->algo.colX = (2 * x / all->info.maplenx) - 1;
		all->cam.rayDirX = all->cam.oriX + all->algo.planeX * all->algo.colX;
		all->cam.rayDirY = all->cam.oriY + all->algo.planeY * all->algo.colX;
		all->cam.mapX = all->cam.posX;
		all->cam.mapY = all->cam.posY;
		all->algo.deltaX = sqrt(1 + (all->cam.rayDirX * all->cam.rayDirY) / (all->cam.rayDirX * all->cam.rayDirY));
		all->algo.deltaY = sqrt(1 + (all->cam.rayDirY * all->cam.rayDirX) / (all->cam.rayDirY * all->cam.rayDirX));
		if (all->cam.rayDirX < 0)
		{
				all->algo.dirX = -1;
				all->algo.longX = (all->cam.posX - all->cam.mapX) * all->algo.deltaX;
		}
		else
		{
				all->algo.dirX = 1;
				all->algo.longX = (all->cam.mapX + 1.0 - all->cam.posX ) * all->algo.deltaX;
		}
		if (all->cam.rayDirY < 0)
		{
				all->algo.dirY = -1;
				all->algo.longY = (all->cam.posY - all->cam.mapY) * all->algo.deltaY;
		}
		else
		{
				all->algo.dirY = 1;
				all->algo.longY = (all->cam.mapY + 1.0 - all->cam.posY) * all->algo.deltaY;
		}
		while (all->algo.hit == 0)
	   	{
			if (all->algo.longX < all->algo.longY)
		   	{
				all->algo.longX += all->algo.deltaX;// agrandis le rayon
				all->cam.mapX += all->algo.dirX;// prochaine case ou case précédente sur X
				all->algo.NSEO = 0;// orientation du mur
			}
	  	 	else
	  	 	{
				all->algo.longY += all->algo.deltaY;// agrandis le rayon
				all->cam.mapY += all->algo.dirY;// prochaine case ou case précédente sur Y
				all->algo.NSEO = 1;// orientation du mur
			}
 				// si le rayon rencontre un mur
			if (all->info.bufmap[all->cam.mapY + (all->cam.mapX * all->info.maplenx)]>0)
				all->algo.hit = 1; // stoppe la boucle 
		}
		if (all->algo.NSEO == 0)
			all->algo.pDist = fabs((all->cam.mapX - all->cam.mapX + (1 - all->algo.dirX) / 2) / all->cam.rayDirX);
		else
			all->algo.pDist = fabs((all->cam.mapY - all->cam.mapY + (1 - all->algo.dirY) / 2) / all->cam.rayDirY);
		all->algo.hauteurLigne = fabs(all->info.resy / all->algo.pDist);
		all->algo.drawstart = (int)(-all->algo.hauteurLigne / 2 + all->info.resy / 2);
		all->algo.drawend = (int)(all->algo.hauteurLigne / 2 + all->info.resy / 2);
		if (all->algo.drawstart < 0)
			all->algo.drawstart = 0;
		if (all->algo.drawend >= all->info.resy)
			all->algo.drawend = all->info.resy - 1;
		y = all->algo.drawstart;
		printf("y%d\n lenx%d\n", y, all->info.resx);
		while (y < all->algo.drawend)
	   	{
		 	int color = 0xf2f2f2;// couleur du pixel pour un mur Nord/Sud
			if (all->algo.NSEO == 1)
				color = 0xCCCCCC;// couleur du pixel pour un mur Est/Ouest
		mlx_pixel_put( all->mlx.ptr, all->mlx.winptr, x, y, color);
			y++;// incrémente la position Y du prochain pixel à tracer
		}
		if (all->algo.drawend < 0) 
			all->algo.drawend = all->info.resy;
		y = all->algo.drawend;
		while (y < all->info.resy)
		{  
			mlx_pixel_put(all->mlx.ptr, all->mlx.winptr, x, y, 0x006666);
			mlx_pixel_put(all->mlx.ptr, all->mlx.winptr, x, all->info.resy - y - 1, 0x006666);
			y++;
		}
		x++;
	}
}
