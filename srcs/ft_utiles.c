/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utiles.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alesanto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 20:26:25 by alesanto          #+#    #+#             */
/*   Updated: 2020/02/05 14:16:48 by alesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void		ft_exit(t_all *all)
{
	if (all->mlx.ptr && all->mlx.winptr)
	{
		mlx_clear_window(all->mlx.ptr, all->mlx.winptr);
		mlx_destroy_window(all->mlx.ptr, all->mlx.winptr);
	}
	if (all->sprites)
		free(all->sprites);
	if (all->info.bufmap)
		free(all->info.bufmap);
	exit(0);
}

void		ft_ifspace(char *line, int *i)
{
	while ((line[*i] == ' ' || line[*i] == '\t' || line[*i] == '\n')
			|| (line[*i] == '\r' || line[*i] == '\v' || line[*i] == '\f'))
		(*i)++;
}
