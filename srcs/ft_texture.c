/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_texture.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alesanto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/19 13:39:55 by alesanto          #+#    #+#             */
/*   Updated: 2020/01/22 18:08:57 by alesanto         ###   ########.fr       */
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

void	ft_textures(t_all *all)
{
	ft_puttexture(all->info.n, &all->textureN, all);
	ft_puttexture(all->info.s, &all->textureS, all);
	ft_puttexture(all->info.e, &all->textureE, all);
	ft_puttexture(all->info.w, &all->textureW, all);
	ft_puttexture(all->info.i, &all->textureI, all);
}
