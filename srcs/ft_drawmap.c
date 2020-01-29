# include "../include/cub3D.h"

t_texture 	ft_mettretexture(t_all *all)
{
	if (all->cam.rayDir.x > 0)
	{
		if (all->algo.NSEO)
		{
			if (all->cam.rayDir.y < 0)
				return (all->textureN);
			return (all->textureS);
		}
		return (all->textureE);
	}
	else
	{
		if (all->algo.NSEO)
		{
			if (all->cam.rayDir.y < 0)
				return (all->textureN);
			return (all->textureS);
		}
		return (all->textureW);
	}
}

void ft_drawall(t_all *all, int x)
{
	double wallX; 
	int	texX;
	int	texY;
	t_texture img;	

	img = ft_mettretexture(all);
	if (all->algo.NSEO == 1)
		wallX = all->cam.raypos.x + all->algo.pDist * all->cam.rayDir.x;
	else
		wallX = all->cam.raypos.y + all->algo.pDist * all->cam.rayDir.y;
	wallX -= floor(wallX);
	texX = wallX * (double)img.w;
	while (all->algo.drawstart < all->algo.drawend)
	{
		texY = (all->algo.drawstart - all->info.res.y / 2 +
				all->algo.hauteurLigne / 2) * img.h / all->algo.hauteurLigne;
		all->mlx.get_data[x + (int)all->algo.drawstart
			* (all->mlx.size_line / 4)] = img.data[texX + texY * img.w];
		all->algo.drawstart++;
	}
}
