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

void     ft_parsing_line(t_all *all, char *line)
{
	int		i;

	i = 0;
	ft_ifspace(line, &i);
//	ft_firstcheck(all, line[i]);
	if (line[i] == 'R' && line[i + 1] == ' ')
		ft_res(all, line);
	else if (line[i] == 'N' && line[i + 1] == 'O' && line[i + 2] == ' ')
		all->info.n = ft_mur(all, line);
	else if (line[i] == 'S' && line[i + 1] == 'O' && line[i + 2] == ' ')
		all->info.s = ft_mur(all, line);
	else if (line[i] == 'W' && line[i + 1] == 'E' && line[i + 2] == ' ')
		all->info.w = ft_mur(all, line);
	else if (line[i] == 'E' && line[i + 1] == 'A' && line[i + 2] == ' ')
		all->info.e = ft_mur(all, line);
	else if (line[i] == 'S' && line[i + 1] == ' ')
		all->info.i = ft_mur(all, line);
	else if (line[i] == 'F' && line[i + 1] == ' ')
		all->info.f = ft_sol(line, all);
	else if (line[i] == 'C' && line[i + 1] == ' ')
		all->info.c = ft_sol(line, all);
	else if (line[i] == '1')
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
