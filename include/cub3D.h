#ifndef CUB3D_H
# define CUB3D_H
# include "../libft/libft.h"
# include "../minilibx_opengl/mlx.h"

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>
# include <fcntl.h>
# include <stdio.h>

typedef struct	s_mlx
{
	void			*ptr;
}				t_mlx;

typedef struct		s_algo
{
    // sur quelle case est la caméra
    int                 mapX;
    int                 mapY;
    // longueur du rayon
    int                 longX;
    int                 longY;
    // longueur du rayon entre chaque intersection
    int                 deltaX;
    int                 deltaY;
    // direction du vecteur sur X et Y (+1 ou -1)
    int                 dirX;
    int                 dirY;
    //le rayon touche un mur ou pas
    int                 hit;
    //quelle orientation à le mur (nord/sud ou est/ouest) dans la map
    int                 NSEO;
    // distance corrigée du rayon
    int                 newlong;
    //la hauteur de la ligne à tracer
    int                 hauteurLigne;
    //les pixels max haut et max bas de la colonne à tracer
    int                 pStart;
    int                 pEnd;
}                   t_algo;

typedef struct		s_info
{
    int                 n;
    int                 s;
    int                 e;
    int                 w;
    int                 i;
    int                 c;
    int                 f;
    int                 resx;
    int                 resy;
    int                 *maplenx;
    int                 mapleny;
    char                *bufmap;
}                   t_info;

typedef struct		s_all
{
    t_algo          algo;
    t_info          info;
    t_mlx           mlx;
}                   t_all;

int		main(int argc, char **argv);

int     ft_parsing(int argc, char **argv, t_all *all);
int     ft_parsing_line(t_all *all, char *line);
int		ft_bufmap(t_all *all, char *line);
int     ft_res(t_all *all, char *line);
int     ft_sol(int *str, char *line);
int     ft_mur(t_all *all, unsigned int **atext, char *line, int *i);

int		initmlx(t_all *all);
void	initall(t_all all);
void    initallsuite(t_all all);

int     ft_ifspace(char *line, int *i);
int     ft_exit(char *s, char *str);

#endif