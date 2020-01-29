char     *ft_mur(t_all *all, char *line)
{
	int		j;
	char	**s;
	char *atext;

	if(!(s = ft_split(line, ' ')))
	{
		ft_printf(ERROR_MALLOC, "s in ft_split in ft_mur");
		ft_exit(all);
	}
	if (!(atext = ft_strdup(s[1])))
	{
		ft_printf(ERROR_MALLOC, "str in ft_mur");
		ft_exit(all);
	}
	j = 0;
	while (s[j])
		free(s[j++]);
	free(s[j]);
	free(s);   
	return (atext);
}

int     ft_sol(char *line, t_all *all)
{
	int i;
	unsigned int color;
	int j;

	i = 0;
	ft_ifspace(line, &i);
	i++;
	ft_ifspace(line, &i);
	color = ft_atoi(&line[i]) * 256 * 256;
	j = ft_isdigit(line[i]) ? 1 : 0;
	while (ft_isdigit(line[i]))
		i++;
	i++;
	color += ft_atoi(&line[i]) * 256;
	j += ft_isdigit(line[i]) ? 1 : 0;
	while (ft_isdigit(line[i]))
		i++;
	i++;
	color += ft_atoi(&line[i]);
	j += ft_isdigit(line[i]) ? 1 : 0;
	if (j !=3)
	{
		ft_printf(ERROR_COLOR);
		ft_exit(all);
	}
	return(color);
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
