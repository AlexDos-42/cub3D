/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_texture.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alesanto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/19 13:39:55 by alesanto          #+#    #+#             */
/*   Updated: 2020/02/04 21:25:43 by alesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

t_texture		ft_puttexture(char *texture_addr, t_all *all)
{
	t_texture texture;

	if (!(texture.ptr = mlx_xpm_file_to_image(all->mlx.ptr,
		texture_addr, &texture.w, &texture.h)))
	{
		ft_printf("Error\nmlx_xpm_file_to_image");
		ft_exit(all);
	}
	if (!(texture.data = (int *)mlx_get_data_addr(texture.ptr,
		&texture.bpp, &texture.line_size, &texture.endian)))
	{
		ft_printf("Error\nmlx_get_data_addr texture");
		ft_exit(all);
	}
	return (texture);
}

t_mlx			ft_texturespr(char *texture_addr, t_all *all)
{
	t_mlx texture;

	if (!(texture.ptr = mlx_xpm_file_to_image(all->mlx.ptr,
		texture_addr, &texture.w, &texture.h)))
	{
		ft_printf("Error\nmlx_xpm_file_to_image");
		ft_exit(all);
	}
	if (!(texture.get_data = (int *)mlx_get_data_addr(texture.ptr,
		&texture.bits_per_pixel, &texture.size_line, &texture.endian)))
	{
		ft_printf("Error\nmlx_get_data_addr texture");
		ft_exit(all);
	}
	return (texture);
}

void			ft_textures(t_all *all)
{
	int			i;
	char		*text;

	i = -1;
	all->texturen = ft_puttexture(all->info.n, all);
	all->textures = ft_puttexture(all->info.s, all);
	all->texturee = ft_puttexture(all->info.e, all);
	all->texturew = ft_puttexture(all->info.w, all);
	while (++i < all->spr.nbsp)
	{
		text = all->info.i;
//		if (all->mvt.diffsp == 1)
//		{
//			if (i % 2 == 1)
//				text = "./objet/KODOS.xpm";
//		}
		all->sprites[i].img = ft_texturespr(text, all);
	}
}
