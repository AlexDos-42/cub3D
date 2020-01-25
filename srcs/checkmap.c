void	check_edges(t_all *all)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while (x < all->info.map.x)
	{
		if (all->info.bufmap[x] != '1' || all->info.bufmap[x + info.map.x * info.map.y] != '1' )
	  {
      ft_exit(all);
    }
		x++;
	}
  x = 0;
	y = 0;
	while (y < all->info.map.x)
	{
		if (all->info.bufmap[x] \
			|| cub->map[x][ft_strlen(cub->map[x]) - 1] != '1')
			return (0);
		x++;
	}
	return (1);
}
