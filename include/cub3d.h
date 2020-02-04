/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alesanto <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 17:44:34 by alesanto          #+#    #+#             */
/*   Updated: 2020/02/04 18:00:21 by alesanto         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include "../libft/libft.h"

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>
# include <fcntl.h>
# include <mlx.h>
# include "error.h"

typedef struct		s_coor
{
	int				x;
	int				y;
}					t_coor;

typedef struct		s_dcoor
{
	double			x;
	double			y;
}					t_dcoor;

typedef struct		s_bmp
{
	int				size;
	char			*img;
	unsigned char	header[14];
	unsigned char	info[40];
	unsigned char	pad[3];
	int				color;
	int				fd;
}					t_bmp;

typedef struct		s_mlx
{
	void			*ptr;
	void			*winptr;
	void			*imgptr;
	int				bits_per_pixel;
	int				size_line;
	int				endian;
	int				*get_data;
	int				w;
	int				h;
	int				color;
}					t_mlx;

typedef struct		s_mvt
{
	t_coor			up;
	t_coor			side;
	t_coor			rot;
	int				hud;
	int				msc;
	double			life;
	int				diffsp;
}					t_mvt;

typedef struct		s_cam
{
	t_dcoor			pos;
	t_dcoor			raypos;
	t_coor			map;
	t_dcoor			ori;
	t_dcoor			raydir;
	int				isit;
	double			speed;
	double			vitrot;
}					t_cam;

typedef struct		s_algo
{
	t_dcoor			len;
	t_dcoor			delta;
	t_coor			dir;
	int				nseo;
	double			newlong;
	double			hauteurligne;
	t_dcoor			plane;
	double			colx;
	double			pdist;
	double			drawstart;
	double			drawend;
	t_dcoor			trans;
	int				spscreen;
	t_coor			start;
	t_coor			end;
	int				texsp_x;
}					t_algo;

typedef struct		s_texture
{
	void			*ptr;
	int				*data;
	int				bpp;
	int				line_size;
	int				endian;
	int				h;
	int				w;
	int				color;
}					t_texture;

typedef struct		s_info
{
	char			*n;
	char			*s;
	char			*e;
	char			*w;
	char			*i;
	unsigned int	c;
	unsigned int	f;
	t_coor			res;
	t_coor			maplen;
	char			*bufmap;
	int				test[256];
}					t_info;

typedef struct		s_sprites
{
	t_dcoor			coor;
	double			dist;
	int				ordre;
	t_mlx			img;
}					t_sprites;

typedef struct		s_spr
{
	int				nbsp;
	t_dcoor			camsp;
	t_dcoor			trans;
	t_coor			start;
	t_coor			end;
	int				spscreen;
	int				sph;
	int				spw;
	t_coor			texsp;
	double			*distwall;
}					t_spr;

typedef struct		s_all
{
	t_algo			algo;
	t_info			info;
	t_mlx			mlx;
	t_cam			cam;
	t_mvt			mvt;
	t_spr			spr;
	t_texture		texturen;
	t_texture		textures;
	t_texture		texturee;
	t_texture		texturew;
	t_mlx			hand;
	t_mlx			hud;
	t_sprites		*sprites;
}					t_all;

/*
** --MAIN--
*/

int					ft_redcross(t_all *all);
int					main(int argc, char **argv);
void				ft_cub(char *argv);
void				ft_bmpinit(t_all *all);
/*
** --FT_INIT--
*/

void				initmlx(t_all *all);
void				initall(t_all *all, char **argv);
void				ft_refresh(t_all *all);
void				initwindow(t_all *all, char **argv);

/*
** --PARSING--
*/

void				ft_bufmap(t_all *all, char *line);
void				ft_parsing_line(t_all *all, char *line, int i);
void				ft_parsing(char **argv, t_all *all);
void				ft_firstcheck(t_all *all, char c, char d);
void				ft_error(t_all *all);

/*
** --PARSING2--
*/

char				*ft_mur(t_all *all, char *line);
int					ft_sol(char *line, t_all *all);
void				ft_res(t_all *all, char *line);

/*
** --FT_RENDU--
*/

void				ft_hl(t_all *all);
void				ft_algo(t_all *all);
void				ft_initray(t_all *all, int x);
void				ft_reycasting(t_all *all);

/*
** --FT_DRAWMAP--
*/

void				ft_drawall(t_all *all, int x);
t_texture			ft_mettretexture(t_all *all);
void				ft_drawall(t_all *all, int x);

/*
** --FT_BMP--
*/

void				ft_bmp(t_all *all);
void				ft_header(t_all *all, t_bmp *bmp);
void				imgbmp(t_all *all, t_bmp *bmp);
void				set_header(unsigned char *header, int param);

/*
** --FT_VERIF_MAP--
*/

void				verify_map(t_all *all);
void				ft_checkline(char *line, int j, t_all *all);
void				posdepart(t_all *all, int x, int y, char dir);
void				ft_checkones(t_all *all);

/*
** --FT_UTILS--
*/

void				ft_ifspace(char *line, int *i);
void				ft_exit(t_all *all);

/*
** --FT_TEXTURES--
*/

void				ft_textures(t_all *all);
t_texture			ft_puttexture(char *texture_addr, t_all *all);
t_mlx				ft_texturespr(char *texture_addr, t_all *all);

/*
** --FT_SPRITES--
*/

void				ft_sprites(t_all *all);
void				get_color(t_all *all, int i);
void				sp_draw(t_all *all, int x, int i);
void				init_sprites(t_all *all);

/*
** --FT_SPRITESPOS--
*/

void				ft_sort(t_all *all);
void				ft_sort_sp(t_all *all);
void				sp_position(t_all *all, int i);
void				sp_dimension(t_all *all);

/*
** --FT_KEYS--
*/

int					ft_keys(t_all *all);
void				ft_moverot(t_all *all);
int					ft_block(t_all *all);
void				ft_moveside(t_all *all);
void				ft_moveup(t_all *all);

/*
** --FT_PUSH--
*/

void				ft_pushlife(int key, t_all *all);
void				ft_pushmsc(int key, t_all *all);
int					ft_push(int key, t_all *all);
int					ft_depush(int key, t_all *all);

/*
** --FT_HAND--
*/

void				ft_draw_hand(t_all *all);
void				load_textures(t_all *all);
t_mlx				resize_image(t_all *all, int width, int height);

/*
** --FT_HUD--
*/

void				ft_draw_hud(t_all *all);
void				load_hudtex(t_all *all);
t_mlx				resize_imagehud(t_all *all, int width, int height);

/*
** --FT_BONUS--
*/

t_mlx				*new_image(t_all *all, int x_len, int y_len);
void				vie_img(t_all *all);
void				draw_vie(t_all *all);

#endif
