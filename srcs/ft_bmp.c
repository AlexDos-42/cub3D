/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bmp.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alesanto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 17:45:20 by alesanto          #+#    #+#             */
/*   Updated: 2020/02/04 17:56:17 by alesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void		set_header(unsigned char *header, int param)
{
	header[0] = (unsigned char)(param);
	header[1] = (unsigned char)(param >> 8);
	header[2] = (unsigned char)(param >> 16);
	header[3] = (unsigned char)(param >> 24);
}

void		imgbmp(t_all *all, t_bmp *bmp)
{
	int i;
	int j;
	int x;
	int y;

	j = -1;
	while (++j < all->info.res.y)
	{
		i = -1;
		while (++i < all->info.res.x)
		{
			x = i;
			y = all->info.res.y - 1 - j;
			bmp->color = all->mlx.get_data[x + y * all->info.res.x];
			write(bmp->fd, &bmp->color, 3);
		}
		i = -1;
		while (++i < (4 - (all->info.res.x * 3) % 4) % 4)
			write(bmp->fd, &bmp->pad, 1);
	}
}

void		ft_header(t_all *all, t_bmp *bmp)
{
	int i;

	i = 0;
	while (i < 14)
		bmp->header[i++] = 0;
	bmp->header[0] = 'B';
	bmp->header[1] = 'M';
	bmp->header[10] = 54;
	i = 0;
	while (i < 40)
		bmp->info[i++] = 0;
	bmp->info[0] = 40;
	bmp->info[12] = 1;
	bmp->info[14] = 24;
	i = 0;
	while (i < 3)
		bmp->pad[i++] = 0;
	set_header(&bmp->header[2], bmp->size);
	set_header(&bmp->info[4], all->info.res.x);
	set_header(&bmp->info[8], all->info.res.y);
	write(bmp->fd, bmp->header, 14);
	write(bmp->fd, bmp->info, 40);
}

void		ft_bmp(t_all *all)
{
	t_bmp	bmp;
	int		imgsize;

	imgsize = 3 * all->info.res.x * all->info.res.y;
	bmp.size = 54 + imgsize;
	bmp.img = malloc((sizeof(char) * imgsize));
	ft_memset(bmp.img, 0, imgsize);
	bmp.fd = open("img.bmp", O_CREAT | O_WRONLY, S_IRWXU);
	ft_header(all, &bmp);
	imgbmp(all, &bmp);
	free(bmp.img);
	close(bmp.fd);
}
