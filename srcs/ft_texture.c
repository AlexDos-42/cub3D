void	ft_puttexture(t_image *texture, char *texture_path)
{	
  int h;
  int w;
  
  h = 64;
  w = 64;
	if (!(texture->ptr = mlx_xpm_file_to_image(all->mlx.ptr, texture_path, &i, &j)))
  {
		printf("Error\nmlx_new_window");
		ft_exit(all);
	}
	if (!(texture->data = (int *)mlx_get_data_addr(texture->ptr, &texture->bpp,	&texture->line_size, &texture->endian)))
	{
		printf("Error\nmlx_new_window");
		ft_exit(all);
	}
}

void	init_textures(t_all all)
{
	ft_puttexture(all->info.notext, all->info.n);
	ft_puttexture(all->info.sotext, all->info.s);
	ft_puttexture(all->info.etext, all->info.e);
	ft_puttexture(all->info.wtext, all->info.w);
	ft_puttexture(all->info.stex, all->info.s);
}