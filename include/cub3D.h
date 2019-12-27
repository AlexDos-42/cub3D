#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include "../minilibx_opengl/mlx_int.h"

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>
# include <fcntl.h>

typedef struct		s_all
{
    s_algo          algo;
    s_info          info;
}                   t_all;

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
}                   t_info;
