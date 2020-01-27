/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_texture.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alesanto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/19 13:39:55 by alesanto          #+#    #+#             */
/*   Updated: 2020/01/27 12:50:27 by alesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/cub3D.h"

t_texture	ft_puttexture(char *texture_addr, t_all *all)
{	
	t_texture texture;

	if (!(texture.ptr = mlx_xpm_file_to_image(all->mlx.ptr, texture_addr, &texture.w, &texture.h)))
  	{
		ft_printf("Error\nmlx_xpm_file_to_image");
		ft_exit(all);
	}
	if (!(texture.data = (int *)mlx_get_data_addr(texture.ptr, &texture.bpp, &texture.line_size, &texture.endian)))
	{
		ft_printf("Error\nmlx_get_data_addr texture");
		ft_exit(all);
	}
	return(texture);
}

t_mlx	ft_texturespr(char *texture_addr, t_all *all)
{	
	t_mlx texture;

	if (!(texture.ptr = mlx_xpm_file_to_image(all->mlx.ptr, texture_addr, &texture.w, &texture.h)))
  	{
		ft_printf("Error\nmlx_xpm_file_to_image");
		ft_exit(all);
	}
	if (!(texture.get_data = (int *)mlx_get_data_addr(texture.ptr, &texture.bits_per_pixel, &texture.size_line, &texture.endian)))
	{
		ft_printf("Error\nmlx_get_data_addr texture");
		ft_exit(all);
	}
	return(texture);
}


void	ft_textures(t_all *all)
{
	int i;

	i = -1;
	all->textureN = ft_puttexture(all->info.n, all);
	all->textureS = ft_puttexture(all->info.s, all);
	all->textureE = ft_puttexture(all->info.e, all);
	all->textureW = ft_puttexture(all->info.w, all);
	printf("all->textureN.w %d\n", all->textureN.w);
	while (++i < all->spr.nbsp)
		all->sprites[i].img = ft_texturespr(all->info.i, all);;
}
