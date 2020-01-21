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
