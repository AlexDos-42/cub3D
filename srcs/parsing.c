/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alesanto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 20:28:56 by alesanto          #+#    #+#             */
/*   Updated: 2020/01/29 23:02:29 by alesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void		ft_bufmap(t_all *all, char *line)
{
	char	*newline;

	if (!(newline = ft_strtrim(line, " ")))
	{
		ft_printf(ERROR_MALLOC, "newline in ft_strtrim");
		ft_exit(all);
	}
	newline = ft_suprspace(newline);
	if (all->info.maplen.y == 0)
	{
		all->info.maplen.x = ft_strlen(newline);
		if (!(all->info.bufmap = ft_strdup(newline)))
		{
			ft_printf(ERROR_MALLOC, "info.bufmap in ft_strdup");
			ft_exit(all);
		}
	}
	else
	{
		if (all->info.maplen.x != ft_strlen(newline))
		{
			ft_printf(ERROR_LENLINE, ++all->info.maplen.y,
				ft_strlen(newline), all->info.maplen.x);
			ft_exit(all);
		}
		if (!(all->info.bufmap = ft_strjoin(all->info.bufmap, newline, 1)))
		{
			ft_printf(ERROR_MALLOC, "info.bufmap in ft_strjoin");
			ft_exit(all);
		}
	}
	ft_strdel(&newline);
	all->info.maplen.y += 1;
}

void		ft_firstcheck(t_all *all, char c, char d)
{
	if (!c)
		return ;
	if (c == 'S' && d == 'O')
		c = 'U';
	if (all->info.test[(int)c] == 0) 
		all->info.test[(int)c] += 1;
	else if (c != '1')
	{
			ft_printf(ERROR_DOUBLE, c);
			ft_exit(all);
	}
	if (c == '1')
	{
		if (!(all->info.test[(int)'N'] == 1 && all->info.test[(int)'U']
			== 1 && all->info.test[(int)'W'] == 1 && all->info.test[(int)'E']
			== 1 && all->info.test[(int)'S'] == 1 && all->info.test[(int)('F')]
			== 1 && all->info.test[(int)'C'] == 1))
		{	
			ft_printf(ERROR_MAPP);
			ft_exit(all);
		}
	}		
	if (c != '1' && (all->info.test[(int)'1'] == 1))
	{	
		ft_printf(ERROR_MAPLAST);
		ft_exit(all);
	}

}

void		ft_parsing_line(t_all *all, char *line)
{
	int		i;

	i = 0;
	ft_ifspace(line, &i);
	ft_firstcheck(all, line[i], line[i + 1]);
	if (line[i] == 'R' && line[i + 1] == ' ')
		ft_res(all, line);
	else if (line[i] == 'N' && line[i + 1] == 'O' && line[i + 2] == ' ')
		all->info.n = ft_mur(all, line);
	else if (line[i] == 'S' && line[i + 1] == 'O' && line[i + 2] == ' ')
		all->info.s = ft_mur(all, line);
	else if (line[i] == 'W' && line[i + 1] == 'E' && line[i + 2] == ' ')
		all->info.w = ft_mur(all, line);
	else if (line[i] == 'E' && line[i + 1] == 'A' && line[i + 2] == ' ')
		all->info.e = ft_mur(all, line);
	else if (line[i] == 'S' && line[i + 1] == ' ')
		all->info.i = ft_mur(all, line);
	else if (line[i] == 'F' && line[i + 1] == ' ')
		all->info.f = ft_sol(line, all);
	else if (line[i] == 'C' && line[i + 1] == ' ')
		all->info.c = ft_sol(line, all);
	else if (!line[i])
		;
	else if (line[i] == '1')
		ft_bufmap(all, line);
	else if (line != '\0')
	{
		ft_printf(ERROR_PARS);
		ft_exit(all);
	}
}

void		ft_parsing(char **argv, t_all *all)
{
	int			ret;
	char		*line;
	int			fd;

	if ((fd = open(argv[1], O_RDONLY)) == -1)
	{
		ft_printf(ERROR_FD);
		ft_exit(all);
	}
	line = NULL;
	ret = 1;
	while ((ret = get_next_line(fd, &line)) == 1)
	{
		if (ret == -1)
		{
			ft_printf(ERROR_GNL, ret);
			ft_exit(all);
		}
		ft_parsing_line(all, line);
		ft_strdel(&line);
	}
	close(fd);
	verify_map(all);
}
