/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rendu.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alesanto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 13:33:50 by alesanto          #+#    #+#             */
/*   Updated: 2020/01/13 22:02:06 by alesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/cub3D.h"

void ft_reycasting(t_all *all)
{
	int x;
	int y;

	x = 0;
	while (x < all->info.res.x)
	{
		printf("x %d\n", x);
		printf("all->info.res.x %d\n", all->info.res.x);
		all->algo.hit = 0;
		printf("all->info.maplen.x %d\n", all->info.maplen.x );
		all->algo.colX = 2.0 * x / (double)all->info.res.x - 1;
		printf("all->algo.colX %f\n", all->algo.colX );
		all->cam.raypos.x = all->cam.pos.x;
		all->cam.raypos.y = all->cam.pos.y;
		printf("all->cam.pos.x %d\n", all->cam.pos.x);
		printf("all->cam.pos.y %d\n", all->cam.pos.y);
		printf("all->algo.plane.x %f\n", all->algo.plane.x);
		printf("all->algo.plane.y %f\n", all->algo.plane.y);
		printf("all->cam.ori.x %f\n", all->cam.ori.x);
		printf("all->cam.ori.y %f\n", all->cam.ori.y);
		all->cam.rayDir.x = all->cam.ori.x + all->algo.plane.x * all->algo.colX;
		all->cam.rayDir.y = all->cam.ori.y + all->algo.plane.y * all->algo.colX;
		all->cam.map.x = (int)(all->cam.raypos.x);
		all->cam.map.y = (int)(all->cam.raypos.y);
		all->algo.delta.x = fabs(1 / all->cam.rayDir.x);
		all->algo.delta.y = fabs(1 / all->cam.rayDir.y);
		printf("all->algo.delta.x %f\n", all->algo.delta.x);
		printf("all->algo.delta.y %f\n", all->algo.delta.y);
		printf("all->cam.rayDir.x %f\n",all->cam.rayDir.x );
		printf("all->cam.raypos.x %d\n", all->cam.raypos.x);
		printf("all->cam.map.x %d\n", all->cam.map.x);
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
		printf("all->algo.len.x %f\n", all->algo.len.x);
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
			printf("case %c\n", all->info.bufmap[all->cam.map.y + (all->cam.map.x * all->info.maplen.x)]);
		while (all->algo.hit == 0)
	   	{
			if (all->algo.len.x < all->algo.len.y)
		   	{
		printf("all->algo.len.x %f\n", all->algo.len.x);
				all->algo.len.x += all->algo.delta.x;
				all->cam.map.x += all->algo.dir.x;
				all->algo.NSEO = 0;
		printf("all->algo.len.x %f\n", all->algo.len.x);
			}
	  	 	else
	  	 	{
		printf("all->algo.len.y %f\n", all->algo.len.y);
				all->algo.len.y += all->algo.delta.y;
				all->cam.map.y += all->algo.dir.y;
				all->algo.NSEO = 1;
		printf("all->algo.len.y %f\n", all->algo.len.y);
			}
			printf("case %c\n", all->info.bufmap[all->cam.map.y + (all->cam.map.x * all->info.maplen.x)]);
			printf("map y : %d | x : %d | maplen.x : %d\n", all->cam.map.y, all->cam.map.x, all->info.maplen.x);
			printf("all->algo.hit 1  %d\n", all->algo.hit);
			if (all->info.bufmap[all->cam.map.x + (all->cam.map.y * all->info.maplen.x)] == '1')
				all->algo.hit = 1;  
			printf("all->algo.hit 2 %d\n", all->algo.hit);
		}
		printf("all->algo.dir.x %d\n", all->algo.dir.x);
		printf("NSEO %d\n", all->algo.NSEO);
		printf("all->cam.raypos.y %d\n", all->cam.raypos.y);
		printf("all->cam.map.y %d\n", all->cam.map.y);
		printf("all->algo.dir.y %d\n", all->algo.dir.y);
		printf("all->cam.rayDir.y %f\n", all->cam.rayDir.y);
		if (all->algo.NSEO == 0)
			all->algo.pDist = (all->cam.map.x - all->cam.raypos.x + (1 - all->algo.dir.x) / 2) / all->cam.rayDir.x;
		else
			all->algo.pDist = (all->cam.map.y - all->cam.raypos.y + (1 - all->algo.dir.y) / 2) / all->cam.rayDir.y;
		printf("all->algo.pDist %f\n", all->algo.pDist);
		all->algo.hauteurLigne = ((int)(all->info.res.y / all->algo.pDist));
		printf("all->algo.hauteurLigne %f\n", all->algo.hauteurLigne);
		all->algo.drawstart = (-all->algo.hauteurLigne / 2 + all->info.res.y / 2);
		all->algo.drawend = (all->algo.hauteurLigne / 2 + all->info.res.y / 2);
		printf("all->algo.drawstart %f\n", all->algo.drawstart);
		printf("all->algo.drawend %f\n", all->algo.drawend);
		if (all->algo.drawstart < 0)
			all->algo.drawstart = 0;
		if (all->algo.drawend >= all->info.res.y)
			all->algo.drawend = all->info.res.y - 1;
		y = all->algo.drawstart;
		printf("y %d\n" , y);
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
		printf("len end %f\n", all->algo.len.x);
//		if (all->algo.hauteurLigne >= 680 )
//		if (x == (all->info.res.x / 2) + 1)
//		if (x == 5)
//			break;
		x++;
	}
}
