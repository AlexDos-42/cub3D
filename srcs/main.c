/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alesanto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 20:06:07 by alesanto          #+#    #+#             */
/*   Updated: 2020/01/11 20:06:11 by alesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../include/cub3D.h"

int		main(int argc, char **argv)
{
	t_all	all;

	initall(&all);
	ft_parsing(argc, argv, &all);
	initmlx(&all);
	return (0);
}
