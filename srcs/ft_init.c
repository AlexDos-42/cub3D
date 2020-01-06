# include "../include/cub3D.h"

int		initmlx(t_all *all)
{
	if (!(all->mlx.ptr = mlx_init()))
		return (ft_exit(NULL, "Error\nmlx_init"));
	if (!(all->mlx.winptr = mlx_new_window(all->mlx.ptr, all->info.resx, all->info.resy, "cub3D")))
		return (ft_exit(NULL, "Error\nmlx_new_window"));
    if (!(all->mlx.imgptr = mlx_new_image(all->mlx.ptr, all->info.resx, all->info.resy)))
        return (ft_exit(NULL, "Error\nmlx_new_image"));
 //  if (!(all->mlx.get_data = (int*)mlx_get_data_addr(all->mlx.imgptr, &all->mlx.bits_per_pixel, all->mlx.size_line, &all->mlx.endian)))
//        return (ft_exit(NULL, "Error\nmlx_get_data_addr"));
}

void initcam(t_all all)
{
    t_cam  cam;

    all.cam = cam;
    cam.posX = 0;
    cam.posY = 0;
    cam.oriX = 0;
    cam.oriY = 0;
    cam.isit = 0;
}

void initallsuite(t_all all)
{
    t_algo  algo;

    all.algo = algo;
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
    all.info.blocx = NULL;
    all.info.blocx = NULL;
    initcam(all);
}

void	initall(t_all all)
{
    t_mlx	mlx;
	t_info	info;

    mlx.ptr = NULL;
    mlx.winptr = NULL;
    mlx.imgptr = NULL;
    mlx.bits_per_pixel = 0;
    mlx.size_line = 0;
    mlx.endian = 0;
    mlx.get_data = 0;
	all.mlx = mlx;
	all.info = info;
    info.n = NULL;
    info.s = NULL;
    info.e = NULL;
    info.w = NULL;
    info.i = NULL;
    info.c = 0;
    info.f = 0;
    info.resy = 0;
    info.resy = 0;
    info.maplenx = NULL;
    info.mapleny = 0;
    info.bufmap = NULL;
    initallsuite(all);
}