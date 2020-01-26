/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_texture.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alesanto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/19 13:39:55 by alesanto          #+#    #+#             */
/*   Updated: 2020/01/26 18:07:55 by alesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/cub3D.h"

void	ft_puttexture(char *texture_addr, t_texture *texture, t_all *all)
{	
	if (!(texture->ptr = mlx_xpm_file_to_image(all->mlx.ptr, texture_addr, &all->texture.w, &all->texture.h)))
  	{
		ft_printf("Error\nmlx_xpm_file_to_image");
		ft_exit(all);
	}
	if (!(texture->data = (int *)mlx_get_data_addr(texture->ptr, &texture->bpp, &texture->line_size, &texture->endian)))
	{
		ft_printf("Error\nmlx_get_data_addr texture");
		ft_exit(all);
	}
}

void	ft_texturespr(char *texture_addr, t_mlx *mlx, t_all *all)
{	
	if (!(mlx->imgptr = mlx_xpm_file_to_image(all->mlx.ptr, texture_addr, &all->mlx.w, &all->mlx.h)))
 	{
		ft_printf("Error\nmlx_xpm_file_to_image");
		ft_exit(all);
	}
	if (!(mlx->get_data = (int *)mlx_get_data_addr(mlx->imgptr, &mlx->bits_per_pixel, &mlx->size_line, &mlx->endian)))
	{
		ft_printf("Error\nmlx_get_data_addr texture");
		ft_exit(all);
	}
}

void	ft_textures(t_all *all)
{
	int i;

	i = 0;
	ft_puttexture(all->info.n, &all->textureN, all);
	ft_puttexture(all->info.s, &all->textureS, all);
	ft_puttexture(all->info.e, &all->textureE, all);
	ft_puttexture(all->info.w, &all->textureW, all);
	while (i < all->spr.nbsp)
	{
		ft_texturespr(all->info.w, &all->sprites[i].img, all);
		i++;
	}
}
