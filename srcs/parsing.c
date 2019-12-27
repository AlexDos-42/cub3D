# include "../include/cub3D.h"

int     ft_exit(char *s, char *str)
{
    ft_printf("%s\n", str);
    if (s)
        free(s);
    return(-1);
}

int     ft_ifspace(char *line, int *i)
{
    while ((line[*i] == ' ' || line[*i] == '\t' || line[*i] == '\n')
	|| (line[*i] == '\r' || line[*i] == '\v' || line[*i] == '\f'))
		(*i)++;
}


int     ft_mur(t_all *all, unsigned int *adr, char *line, int *i)
{
	char	*str;
	int		j;

	(*i) += 2;
	ft_ifspace(line, i);
	j = *i;
	while (line[*i] != ' ' && line[*i] != '\0')
		(*i)++;
	if (!(str = ft_calloc(sizeof(char), (*i - j + 1))))
        return (0);
	*i = j;
	j = 0;
	while (line[*i] != ' ' && line[*i] != '\0')
		str[j++] = line[(*i)++];
	str[j] = '\0';
    return(1);
}

int     ft_sol(int *str, char *line)
{
    int i;

    i = 0;
    ft_ifspace(line, &i);
	i++;
	*str = ft_atoi(line) * 256 * 256;
    while (ft_isdigit)
        i++;
	i++;
	*str += ft_atoi(line) * 256;
    while (ft_isdigit)
        i++;
	i++;
	*str += ft_atoi(line);
    if (!*str)
        return (0);
    return(1);

}

int     ft_res(t_all *all, char *line)
{
    int i;

    i = 0;
    ft_ifspace(line, &i);
	i++;
	all->info.resx = ft_atoi(&line[i]);
    while (ft_isdigit)
        i++;
	all->info.resy = ft_atoi(&line[i]);
	if (all->info.resx > 2560)
		all->info.resx = 2560;
	if (all->info.resy > 1400)
		all->info.resy = 1400;
    if (!all->info.resx || all->info.resy)
        return (0);
    return (1);
}

int		ft_map(t_all *all, char *line, int i)

int     ft_parsing_line(t_all *all, char *line)
{
	int		i;

	ft_ifspace(line, &i);
	if ((line[i] == 'R' && line[i + 1] == ' ') && !ft_res(all, line))
        return (0);
	else if ((line[i] == 'N' && line[i + 1] == 'O' && line[i + 2] == ' ') && !ft_mur(all, &all->info.n, line, &i))
        return (0);
	else if ((line[i] == 'S' && line[i + 1] == 'O' && line[i + 2] == ' ') && !ft_mur(all, &all->info.s, line, &i))
        return (0);
	else if ((line[i] == 'W' && line[i + 1] == 'E' && line[i + 2] == ' ') && !ft_mur(all, &all->info.w, line, &i))
        return (0);
	else if ((line[i] == 'E' && line[i + 1] == 'A' && line[i + 2] == ' ') && !ft_mur(all, &all->info.e, line, &i))
        return (0);
	else if ((line[i] == 'S' && line[i + 1] == ' ') && !ft_mur(all, &all->info.i, line, &i))
        return (0);
	else if ((line[i] == 'F' && line[i + 1] == ' ') && !ft_sol(&all->info.f, line))
        return (0);
	else if ((line[i] == 'C' && line[i + 1] == ' ') && !ft_sol(&all->info.c, line))
        return (0);
	else if ((line[i] == '1' && line[i + 1] == ' ') && !ft_map(all, line, &i))
        return (0);
    return (1);
}

int     ft_parsing(int argc, char **argv, t_all *all)
{
    int         ret;
    char        *line;
    int         fd;

    if (argc == 0 || argc > 3)
		return (ft_exit(NULL, "Error : argc != 1 || 2"));
	if (!(fd = open(argv[1], O_RDONLY)))
		return (ft_exit(NULL, "Error : fd error"));
	if (!t_info_init(*all, argc, argv))
		return (ft_exit(NULL, "Error : argv[2] not valid"));
	line = NULL;
	ret = 1;
	while ((ret = get_next_line(argv, &line)) == 1)
	{
		if (!ft_parsing_line(all->info, line))
			return (ft_exit(all->info, "Error : Parsing error"));
		ft_strdel(&line);
	}
	close(fd);
	return (1);
}