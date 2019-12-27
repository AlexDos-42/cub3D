# include "../include/cub3D.h"

int		main(int argc, char **argv)
{
	t_all	*all;

	if (!(ft_parsing(argc, argv, &all)))
			return (-1);
	if (!(build_map(*all)))
		return (ft_exit(*all, "Error\nMap is not valid\n"));

	return (0);
}