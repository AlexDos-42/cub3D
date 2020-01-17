/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rendu.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alesanto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 13:33:50 by alesanto          #+#    #+#             */
/*   Updated: 2020/01/17 13:42:01 by alesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/cub3D.h"

void	ft_hit(t_all *all)
{
		while (all->algo.hit == 0)
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
				all->algo.hit = 1;  
		}
		if (all->algo.NSEO == 0)
			all->algo.pDist = (all->cam.map.x - all->cam.raypos.x
					+ (1.0 - all->algo.dir.x) / 2) / all->cam.rayDir.x;
		else
			all->algo.pDist = (all->cam.map.y - all->cam.raypos.y
					+ (1.0 - all->algo.dir.y) / 2) / all->cam.rayDir.y;
		all->algo.hauteurLigne = ((int)(all->info.res.y / all->algo.pDist));
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

void ft_reycasting(t_all *all)
{
	int x;
	int y;
	x = 0;


	printf("reycasting");
	printf("all->cam.pos.x %f\n", all->cam.pos.x);
	printf("all->cam.pos.y %f\n", all->cam.pos.y);
	while (x < all->info.res.x)
	{
		all->algo.hit = 0;
		all->algo.colX = 2 * x / (double)all->info.res.x - 1;
		all->cam.raypos = (t_dcoor){all->cam.pos.x, all->cam.pos.y};
		all->cam.rayDir.x = all->cam.ori.x + all->algo.plane.x * all->algo.colX;
		all->cam.rayDir.y = all->cam.ori.y + all->algo.plane.y * all->algo.colX;
		all->cam.map = (t_coor){(int)(all->cam.raypos.x), (int)(all->cam.raypos.y)};
		all->algo.delta.x = fabs(1 / all->cam.rayDir.x);
		all->algo.delta.y = fabs(1 / all->cam.rayDir.y);
		ft_algo(all);
		ft_hit(all);
		all->algo.drawstart = (-all->algo.hauteurLigne / 2 + all->info.res.y / 2);
		all->algo.drawend = (all->algo.hauteurLigne / 2 + all->info.res.y / 2);
		y = all->algo.drawstart;
		if (all->algo.drawstart < 0)
		{
			y = -all->algo.drawstart;
			all->algo.drawstart = 0;
		}
		if (all->algo.drawend >= all->info.res.y)
			all->algo.drawend = all->info.res.y - 1;
		while (y < all->algo.drawend)
	   	{
		 	int color = 0xff0000;
			if (all->algo.NSEO == 1)
				color = 0x0000ff;
			all->mlx.get_data[x + y * all->info.res.x] = color;
			y++;
		}
		if (all->algo.drawend < 0) 
			all->algo.drawend = all->info.res.y;
		y = all->algo.drawend;
		while (y < all->info.res.y)
		{  
			all->mlx.get_data[x + y * all->info.res.x] = all->info.c;
			all->mlx.get_data[x + (all->info.res.y - y - 1) * all->info.res.x] = all->info.c;
			y++;
		}
		x++;
	}
	mlx_put_image_to_window (all->mlx.ptr, all->mlx.winptr, all->mlx.imgptr, 0, 0);
	mlx_destroy_image(all->mlx.ptr, all->mlx.imgptr);
}
