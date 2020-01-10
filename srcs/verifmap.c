# include "../include/cub3D.h"

void		posdepart(t_all *all, int x, int y, char dir)
{
	all->cam.posX = x;
	all->cam.posY = y;
	if (dir == 'E')
	{
		all->cam.oriX = 1;
		all->cam.oriY = 0;
	}
	else if (dir == 'S')
	{
		all->cam.oriX = 0;
		all->cam.oriY = 1;
	}
	else if (dir == 'W')
	{
		all->cam.oriX = -1;
		all->cam.oriY = 0;
	}
	else
	{
		all->cam.oriX = 0;
		all->cam.oriY = -1;
	}
	all->cam.isit = 1;
}

int     ft_checkline(char *line, int j, t_all *all)
{
	static int	l;
	int			i;
	int			k;

	i = -1;
	while (++i < all->info.maplenx)
	{
		k = i + (j * all->info.maplenx);
	printf("i %d\nj %d\nk %d\n", i, j,k);
	printf("line[k]  %c\n", line[k]);
	printf("line  %s\n", line);
		if (line[k] == 'N' || line[k] == 'S' || line[k] == 'W' || line[k] == 'E')
			posdepart(all, i, j, line[k]);
		else if (line[k] == '2')
		{
			all->info.blocx[l] = i;
			all->info.blocy[l++] = j;
		}
		else if (line[k] != '1' && line[k] != '0')
			return (0);
	printf("testb\n");
	}
	return (1);
}

int ft_suprspace(cha *str)
{
	int i;
	char tmp;

	i = 0;
	tmp = ft_calloc(1, 1);
	while (str)
	{
		if (str[i] == ' ')
			i++;
		tmp[j] = strjoin(tmp, &str[i], 1)
	}
	free(str);
	str = tmp;
}

int		verify_map(t_all *all)
{
    int		j;
    char *tmp;

    j = -1;
	ft_suprspace(all);
	tmp = all->info.bufmap;
	ft_suprspace(all);
    while (++j < all->info.mapleny)
	{
		if (!(ft_checkline(tmp, j, all)) || all->cam.isit != 1)
			return (0);
	printf("test2\n");
	}
	return (1);
}
