/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bonus.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alesanto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 15:43:34 by alesanto          #+#    #+#             */
/*   Updated: 2020/01/29 15:49:45 by alesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/cub3D.h"

t_mlx		*new_image(t_all *all, int x_len, int y_len)
{
	t_mlx *img;

	if (!(img = ft_calloc(sizeof(t_mlx), 1)))
		ft_exit(all);
	if (!(img->imgptr = mlx_new_image(all->mlx.ptr, x_len, y_len)))
		ft_exit(all);
	img->get_data = (int *)mlx_get_data_addr(img->imgptr, &img->bits_per_pixel,
				&img->size_line, &img->endian);
	img->w = x_len;
	img->h = y_len;
	return (img);
}

void	vie_img(t_all *all)
{
	t_mlx	*img;
	int		x;
	int		y;
	int color;;

	if (!(img = new_image(all,  all->info.res.x * 0.2 , all->info.res.y * 0.04)))
		ft_exit(all);
	img->w = all->info.res.x * 0.2;
	img->h = all->info.res.y * 0.04 ;
	x = 0;
	color = 16770102;
	while (x < img->w - (img->w * all->mvt.life))
	{
		y = 0;
		while (y < img->h)
		{
			img->get_data[x + y * (img->size_line / 4)] = color ;
			y++;
		}
		color++;
		x++;
	}
	mlx_put_image_to_window(all->mlx.ptr, all->mlx.winptr,
			img->imgptr, all->info.res.x * 0.2, all->info.res.y * 0.92);
}

void		draw_vie(t_all *all)
{
	vie_img(all);
	if ((int)all->mvt.life == 1)
	{
		 ft_printf(ERROR_GO);
		 system("afplay objet/homer.wav&");
		 ft_exit(all);
	}
}
