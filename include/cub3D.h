#ifndef CUB3D_H
# define CUB3D_H
# include "../libft/libft.h"

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include <mlx.h>
# include "error.h"

typedef struct	s_coor
{
	int             	x;
	int             	y;
}				t_coor;

typedef struct	s_dcoor
{
	double             	x;
	double             	y;
}				t_dcoor;

typedef struct	s_mlx
{
	void		*ptr;
	void		*winptr;
	void		*imgptr;
	int			bits_per_pixel;
	int			size_line;
	int			endian;
	int			*get_data;
}				t_mlx;

typedef struct	s_mvt
{
	t_coor			up;
	t_coor			side;
	t_coor			rot;
}				t_mvt;

typedef struct		s_cam
{
	// sur quelle case est la caméra
	t_dcoor			pos;
	// position de départ du rayon
	t_dcoor			raypos;
	// quelle case on regarde
	t_coor			map;
	// quelle est l'orientation de la caméra
	t_dcoor			ori;
	// direction du rayon
	t_dcoor			rayDir;
	// est ce que la cam est définie
	int				isit;
	double			speed;
}					t_cam;

typedef struct		s_algo
{
	// longueur du rayon
	t_dcoor			len;
	// longueur du rayon entre chaque intersection
	t_dcoor			delta;
	// direction du vecteur sur X et Y (+1 ou -1)
	t_coor			dir;
	//le rayon touche un mur ou pas
	int				hit;
	//quelle orientation à le mur (nord/sud ou est/ouest) dans la map
	int				NSEO;
	// distance corrigée du rayon
	double			newlong;
	//la hauteur de la ligne à tracer
	double			hauteurLigne;
	// vecteur du plan de projection
	t_dcoor			plane;
	// position de la colonne par rapport au centre de l’écran
	double			colX;
	// Calcule la distance corrigée pour la projection
	double			pDist;
	//Calcule les pixels max haut et max bas de la colonne à tracer
	double			drawstart;
	double			drawend;
}					t_algo;

typedef struct		s_texture
{
	void			*ptr;
	int				*data;
	int				bpp;
	int				line_size;
	int				endian;
}		t_texture;

typedef struct		s_info
{
	char	*n;
	char	*s;
	char	*e;
	char	*w;
	char	*i;
	unsigned int	c;
	unsigned int	f;
	t_coor			res;
	t_coor          maplen;
	char            *bufmap;
	t_coor          *bloc;
	int 			nbbloc;
	t_texture		notext;
	t_texture		sotext;
	t_texture		etext;
	t_texture		wtext;
	t_texture		stext;
}                   t_info;

typedef struct		s_all
{
	t_algo          algo;
	t_info          info;
	t_mlx           mlx;
	t_cam           cam;
	t_mvt			mvt;
	t_texture		textureN;
	t_texture		textureS;
	t_texture		textureE;
	t_texture		textureW;
	t_texture		textureI;
	t_texture		texture;
}                   t_all;

int     ft_redcross(t_all *all);
int		main(int argc, char **argv);

void    ft_parsing(char **argv, t_all *all);
void    ft_parsing_line(t_all *all, char *line);
void	ft_bufmap(t_all *all, char *line);
void    ft_res(t_all *all, char *line);
int   	ft_sol(char *line, t_all *all);
char    *ft_mur(t_all *all, char *line);

void	verify_map(t_all *all);
void    ft_checkline(char *line, int j, t_all *all);
void	posdepart(t_all *all, int x, int y, char dir);

void	initmlx(t_all *all);
void	initall(t_all *all, char **argv);
void	ft_refresh(t_all *all);
void	initwindow(t_all *all);

void    ft_ifspace(char *line, int *i);
void    ft_exit(t_all *all);
t_dcoor ft_dcoor(double x, double y);
t_coor  ft_coor(int x, int y);

int		ft_push(int key, t_all *all);
int		ft_depush(int key, t_all *all);
int		ft_keys(t_all *all);

void	ft_reycasting(t_all *all);

void	ft_textures(t_all *all);
void	ft_puttexture(char *texture_path, t_texture *texture, t_all *all);

#endif
