# include "../include/cub3D.h"

int		main(int argc, char **argv)
{
	t_all	all;

	initall(&all);
	printf("test1\n");
	ft_parsing(argc, argv, &all);
	printf("testend\n");
//	build_map(&all);
	initmlx(&all);
	return (0);
}
