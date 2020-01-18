# include "../include/cub3D.h"

void	ft_bufmap(t_all *all, char *line)
{
	char	*newline;

	if (!(newline = ft_strtrim(line, " ")))
	{
		ft_printf(ERROR_MALLOC, "newline in ft_strtrim");
		ft_exit(all);
	}
	newline = ft_suprspace(newline);
	if (all->info.maplen.y == 0)
	{
		all->info.maplen.x = ft_strlen(newline);
		if (!(all->info.bufmap = ft_strdup(newline)))
		{
			ft_printf(ERROR_MALLOC, "info.bufmap in ft_strdup");
			ft_exit(all);
		}
	}
	else
	{
		if (all->info.maplen.x != ft_strlen(newline))
		{
			ft_printf(ERROR_LENLINE, all->info.maplen.x, ++all->info.maplen.y, ft_strlen(newline));
			ft_exit(all);
		}
		if (!(all->info.bufmap = ft_strjoin(all->info.bufmap, newline, 1)))
		{
			ft_printf(ERROR_MALLOC, "info.bufmap in ft_strjoin");
			ft_exit(all);
		}
	}
	ft_strdel(&newline);
	all->info.maplen.y += 1;
}

void	ft_mlx_get_data_addr(unsigned int **atext, void *img, t_all *all)
{
	*atext = (unsigned int *)mlx_get_data_addr(img, &all->mlx.bits_per_pixel, &all->mlx.size_line, &all->mlx.endian);
	free(img);
	if (*atext == 0)
	{
		ft_printf(ERROR_TEXTURE);
		ft_exit(all);
	}
}

void     ft_mur(t_all *all, char **atext, char *line)
{
	int		j;
	char	**s;
	//	int		width;
	//	int		height;
	//	void	*img;

	if(!(s = ft_split(line, ' ')))
	{
		ft_printf(ERROR_MALLOC, "s in ft_split in ft_mur");
		ft_exit(all);
	}
	if (!(*atext = ft_strdup(s[1])))
	{
		ft_printf(ERROR_MALLOC, "str in ft_mur");
		ft_exit(all);
	}
	j = 0;
	while (s[j])
		free(s[j++]);
	free(s[j]);
	free(s[j]);   
	//	img = mlx_xpm_file_to_image(all->mlx.ptr, str, &width, &height);
	//    return(ft_mlx_get_data_addr(atext, img, all));
}

void     ft_sol(unsigned int *str, char *line, t_all *all)
{
	int i;

	i = 0;
	ft_ifspace(line, &i);
	i++;
	*str = ft_atoi(&line[i]) * 256 * 256;
	while (ft_isdigit(line[i]))
		i++;
	i++;
	*str += ft_atoi(&line[i]) * 256;
	while (ft_isdigit(line[i]))
		i++;
	i++;
	*str += ft_atoi(&line[i]);
	if (!*str)
	{
		ft_printf(ERROR_COLOR);
		ft_exit(all);
	}
}

void     ft_res(t_all *all, char *line)
{
	int i;

	i = 0;
	ft_ifspace(line, &i);
	i++;
	all->info.res.x = ft_atoi(&line[i]);
	i++;
	while (ft_isdigit(line[i]))
		i++;
	all->info.res.y = ft_atoi(&line[i]);
	if (all->info.res.x == 0 || all->info.res.y == 0)
	{
		ft_printf(ERROR_RES, all->info.res.x, all->info.res.y);
		ft_exit(all);
	}
	if (all->info.res.x > 2560)
		all->info.res.x = 2560;
	else if (all->info.res.x < 100)
		all->info.res.x = 100;
	if (all->info.res.y > 1440)
		all->info.res.y = 1440;
	else if (all->info.res.y < 100)
		all->info.res.y = 100;
}

void     ft_parsing_line(t_all *all, char *line)
{
	int		i;

	i = 0;
	ft_ifspace(line, &i);
	if (line[i] == 'R' && line[i + 1] == ' ')
		ft_res(all, line);
	else if (line[i] == 'N' && line[i + 1] == 'O' && line[i + 2] == ' ')
		ft_mur(all, &all->info.n, line);
	else if (line[i] == 'S' && line[i + 1] == 'O' && line[i + 2] == ' ')
		ft_mur(all, &all->info.s, line);
	else if (line[i] == 'W' && line[i + 1] == 'E' && line[i + 2] == ' ')
		ft_mur(all, &all->info.w, line);
	else if (line[i] == 'E' && line[i + 1] == 'A' && line[i + 2] == ' ')
		ft_mur(all, &all->info.e, line);
	else if (line[i] == 'S' && line[i + 1] == ' ')
		ft_mur(all, &all->info.i, line);
	else if (line[i] == 'F' && line[i + 1] == ' ')
		ft_sol(&all->info.f, line, all);
	else if (line[i] == 'C' && line[i + 1] == ' ')
		ft_sol(&all->info.c, line, all);
	else if (line[i] == '1' && line[i + 1] == ' ')
		ft_bufmap(all, line);
	else if(*line != '\0')
	{
		ft_printf(ERROR_PARS, line[i]);
		ft_exit(all);
	}
}

void     ft_parsing(char **argv, t_all *all)
{
	int         ret;
	char        *line;
	int         fd;


	if ((fd = open(argv[1], O_RDONLY)) == -1)
	{
		ft_printf(ERROR_FD);
		ft_exit(all);
	}
	line = NULL;
	ret = 1;
	while ((ret = get_next_line(fd, &line)) == 1)
	{
		if (ret == -1)
		{
			ft_printf(ERROR_GNL, ret);
			ft_exit(all);
		}
		ft_parsing_line(all, line);
		ft_strdel(&line);
	}
	close(fd);
	verify_map(all);
}
