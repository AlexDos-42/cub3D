# include "../include/cub3D.h"

int		initmlx(t_all *all)
{
	if (!(all->mlx.ptr = mlx_init()))
		return (ft_exit(NULL, "Error\nmlx_init"));
	if (!(all->mlx.ptr = mlx_new_window(all->mlx.ptr, all->info.resx, all->info.resy, "cub3D")))
		return (ft_exit(NULL, "Error\nmlx_new_window"));
}

void initallsuite(t_all all)
{
    t_algo  algo;

    all.algo = algo;
    algo.mapX = 0;
    algo.mapY = 0;
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
}

void	initall(t_all all)
{
    t_mlx	mlx;
	t_info	info;

    mlx.ptr = NULL;
	all.mlx = mlx;
	all.info = info;
    info.n = 0;
    info.s = 0;
    info.e = 0;
    info.w = 0;
    info.i = 0;
    info.c = 0;
    info.f = 0;
    info.resy = 0;
    info.resy = 0;
    info.maplenx = NULL;
    info.mapleny = 0;
    info.bufmap = NULL;
    initallsuite(all);
}