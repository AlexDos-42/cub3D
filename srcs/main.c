# include "../include/cub3D.h"

int		main(int argc, char **argv)
{
	t_all	all;

	initall(&all);
	printf("test1\n");
	if (!(ft_parsing(argc, argv, &all)))
			return (-1);
	printf("testend\n");
//	if (!(build_map(&all)))
//		return (ft_exit(all, "Error\nMap is not valid\n"));
	if (!(initmlx(&all)))
		return (-1);
	return (0);
}
