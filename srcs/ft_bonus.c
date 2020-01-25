# include "../include/cub3D.h"
/*
void hands(t_all *all)
{


	while ( all->info.res.y - 100 < all->info.res.y)
	{
		all->mlx.get_data[x + (int)all->algo.drawstart * (all->mlx.size_line / 4)] = img.data[texX + texY * 64];
		all->algo.drawstart++;
	}
}
*/
void	ft_hud(t_all *all)
{
	if (all->mvt.hud == 1)
	{
		mlx_string_put(all->mlx.ptr, all->mlx.winptr, 20, 10, 0xFFFFFF, 
			"Touches :");
		mlx_string_put(all->mlx.ptr, all->mlx.winptr, 20, 10, 0xFFFFFF, 
			"W, A, S, D : move");
		mlx_string_put(all->mlx.ptr, all->mlx.winptr, 20, 30, 0xFFFFFF, 
			"<-, -> : Rotate");
		mlx_string_put(all->mlx.ptr, all->mlx.winptr, 20, 50, 0xFFFFFF, 
			"SHIFT : Sprint");
		mlx_string_put(all->mlx.ptr, all->mlx.winptr, 20, 70, 0xFFFFFF, 
			"Tab: Help");
		mlx_string_put(all->mlx.ptr, all->mlx.winptr, 20, 90, 0xFFFFFF, 
			"ESC : Game Over");
	}
}

t_mlx		*new_image(t_all *all, int x_len, int y_len)
{
	t_mlx *img;

	if (!(img = ft_calloc(sizeof(t_mlx), 1)))
		ft_exit(all);
	if (!(img->imgptr = mlx_new_image(all->mlx.ptr, x_len, y_len)))
		return (void *)0;
	img->get_data = (int *)mlx_get_data_addr(img->imgptr, &img->bits_per_pixel,
				&img->size_line, &img->endian);
	img->w = x_len;
	img->h = y_len;
	return (img);
}

void	vie_img(t_all *all)
{
	t_mlx	*img;
	double	img_w;
	int		x;
	int		y;

	img_w = (int)(((double)191 / (double)20) * 20);
	if (!(img = new_image(all, (int)img_w, 30)))
		ft_exit(all);
	img->w = (int)img_w;
	img->h = 30;
	x = 0;
	while (x < img->w - (img->w * all->mvt.life))
	{
		y = 0;
		while (y < img->h)
		{
			img->get_data[x + y * (img->size_line / 4)] = 15940372;
			y++;
		}
		x++;
	}
	mlx_put_image_to_window(all->mlx.ptr, all->mlx.winptr, img->imgptr, 85, 520);
}

void		draw_vie(t_all *all)
{
	vie_img(all);
//	mlx_put_image_to_window(all->mlx.ptr, all->mlx.winptr,
//		./textures/health.xpm, 40, 500);
}
