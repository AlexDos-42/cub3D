# include "../include/cub3D.h"

void	initmlx(t_all *all)
{
	if (!(all->mlx.ptr = mlx_init()))
	{
		printf("Error\nmlx_init");
		ft_exit(all);
	}
	if (!(all->mlx.winptr = mlx_new_window(all->mlx.ptr, all->info.resx, all->info.resy, "cub3D")))
	{
		printf("Error\nmlx_new_window");
		ft_exit(all);
	}
	if (!(all->mlx.imgptr = mlx_new_image(all->mlx.ptr, all->info.resx, all->info.resy)))
	{
		printf("Error\nmlx_new_image");
		ft_exit(all);
	}
	mlx_string_put (all->mlx.ptr, all->mlx.winptr, 400, 300, all->info.c, "bonjour");
//	mlx_put_image_to_window (all->mlx.ptr, all->mlx.winptr,  all->mlx.imgptr, 0, 0);
	if (!(all->mlx.get_data = (int)mlx_get_data_addr(all->mlx.imgptr, &all->mlx.bits_per_pixel, &all->mlx.size_line, &all->mlx.endian)))
	{
		printf("mlx_get_data_addr");
		ft_exit(all);
	}
//	expose_hook(param);
//  key_hook(keycode, param)
	mlx_loop(all->mlx.ptr);
}

void initcam(t_all *all)
{
	t_cam  cam;

	cam.posX = 0;
	cam.posY = 0;
	cam.oriX = 0;
	cam.oriY = 0;
	cam.isit = 0;
	all->cam = cam;
}

void initallsuite(t_all *all)
{
	t_algo  algo;

	algo.longX = 0;
	algo.longY = 0;
	algo.deltaX = 0;
	algo.deltaY = 0;
	algo.dirX = 0;
	algo.dirY = 0;
	algo.hit = 0;
	algo.NSEO = 0;
	algo.newlong = 0;
	algo.hauteurLigne = 0;
	algo.pStart = 0;
	algo.pEnd = 0;
	all->algo = algo;
	initcam(all);
}

void initinfo(t_all *all)
{
	t_info	info;
	
	info.n = NULL;
	info.s = NULL;
	info.e = NULL;
	info.w = NULL;
	info.i = NULL;
	info.c = 0;
	info.f = 0;
	info.resy = 0;
	info.resy = 0;
	info.maplenx = 0;
	info.mapleny = 0;
	info.bufmap = NULL;
	info.blocx = NULL;
	info.blocx = NULL;
	info.nbbloc = 0;
	info.north_texture = NULL;
	info.south_texture = NULL;
	info.west_texture = NULL;
	info.east_texture = NULL;
	info.sprite_texture = NULL;
	all->info = info;
}
void	initall(t_all *all)
{
	t_mlx	mlx;

	mlx.ptr = NULL;
	mlx.winptr = NULL;
	mlx.imgptr = NULL;
	mlx.bits_per_pixel = 0;
	mlx.size_line = 0;
	mlx.endian = 0;
	mlx.get_data = 0;
	all->mlx = mlx;
	initinfo(all);
	initallsuite(all);
}
