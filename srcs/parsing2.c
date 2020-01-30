/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alesanto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 20:31:28 by alesanto          #+#    #+#             */
/*   Updated: 2020/01/29 20:34:29 by alesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

char		*ft_mur(t_all *all, char *line)
{
	int			j;
	char		**s;
	char		*atext;

	if (!(s = ft_split(line, ' ')))
	{
		ft_printf(ERROR_MALLOC, "s in ft_split in ft_mur");
		ft_exit(all);
	}
	if (!(atext = ft_strdup(s[1])))
	{
		ft_printf(ERROR_MALLOC, "str in ft_mur");
		ft_exit(all);
	}
	if (s[2])
	{
		ft_printf(ERROR_MUR);
		ft_exit(all);
	}	
	j = 0;
	while (s[j])
		free(s[j++]);
	free(s[j]);
	free(s);
	return (atext);
}

void ft_solcheck(t_all *qll,char *line)
{
	j = ft_isdigit(line[i]) ? 1 : 0;
	if (ft_atoi(line[i]) < 0 || ft_atoi(line[i]) > 255)
		j--;
	while (ft_isdigit(line[i]))
		i++;
	j += line[i] == ',' ? 1 : 0;
	j += ft_isdigit(line[++i]) ? 1 : 0;
	if (ft_atoi(line[i]) < 0 || ft_atoi(line[i]) > 255)
		j--;
	while (ft_isdigit(line[i]))
		i++;
	j += line[i] == ',' ? 1 : 0;
	j += ft_isdigit(line[++i]) ? 1 : 0;
	if (ft_atoi(line[i]) < 0 || ft_atoi(line[i]) > 255)
		j--;
	while (ft_isdigit(line[i]))
		i++;
	ft_ifspace(line, &i);
	j -= line[i] != '\0' ? 1 : 0;
	if (j != 5)
	{
		ft_printf(ERROR_COLOR);
		ft_exit(all);
	}
}

int			ft_sol(char *line, t_all *all)
{
	int				i;
	unsigned int	color;
	int				j;

	i = 0;
	ft_ifspace(line, &i);
	i++;
	ft_ifspace(line, &i);
	color = ft_atoi(&line[i]) * 256 * 256;
	while (ft_isdigit(line[i]))
		i++;
	color += ft_atoi(&line[++i]) * 256;
	while (ft_isdigit(line[i]))
		i++;
	color += ft_atoi(&line[++i]);
	return (color);
}

void		ft_res(t_all *all, char *line)
{
	int i;

	i = 0;
	ft_ifspace(line, &i);
	all->info.res.x = ft_atoi(&line[++i]);
	i++;
	while (ft_isdigit(line[i]))
		i++;
	all->info.res.y = ft_atoi(&line[i]);
	if (all->info.res.x <= 0 || all->info.res.y <= 0)
	{
		ft_printf(ERROR_RES, all->info.res.x, all->info.res.y);
		ft_exit(all);
	}
	while (ft_isdigit(line[i]))
		i++;
	ft_ifspace(line, &i);
	if (line[i])
	{
		ft_printf(ERROR_RESO);
		ft_exit(all);
	}
}
