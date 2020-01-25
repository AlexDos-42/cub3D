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

t_image		*new_image(
	t_window *win_infos,
	int x_len,
	int y_len)
{
	t_image *img;

	if (!(img = malloc(sizeof(t_image))))
		return (void *)0;
	ft_bzero(img, sizeof(t_image));
	if (!(img->img_ptr = mlx_new_image(win_infos->mlx_ptr, x_len, y_len)))
		return (void *)0;
	img->data = mlx_get_data_addr(img->img_ptr, &img->bpp,
				&img->size_line, &img->endian);
	img->width = x_len;
	img->height = y_len;
	return (img);
}

static void	health_img(
	t_window *win_infos
)
{
	t_image	*img;
	double	img_width;
	int		x;
	int		y;

	img_width = (int)(((double)191 / (double)20)
		* (double)win_infos->player->health);
	if (!(img = new_image(win_infos, (int)img_width, 30)))
		leave(1, win_infos, "Error init image map");
	img->width = (int)img_width;
	img->height = 30;
	y = 0;
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
		{
			pixel_put_to_image(0x00FF00, x, y, img);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(win_infos->mlx_ptr, win_infos->win_ptr,
		img->img_ptr, 85, 520);
}

void		draw_health(
	t_window *win_infos
)
{
	health_img(win_infos);
	mlx_put_image_to_window(win_infos->mlx_ptr, win_infos->win_ptr,
		win_infos->textures[4]->img_ptr, 40, 500);
}
