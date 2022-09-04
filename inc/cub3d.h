/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 03:43:48 by dtanigaw          #+#    #+#             */
/*   Updated: 2022/09/04 04:08:21 by mint             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stddef.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <errno.h>
# include <limits.h>
# include "cub3d_parser.h"
# include "get_next_line.h"

# include <math.h>
# include <stdbool.h>
# include <fcntl.h>
# include <X11/keysym.h>
# include <mlx.h>
# include <X11/X.h>

# define _TITLE		"cub3d"
/*
# define _SCREENW	640
# define _SCREENH	480
*/
# define _SCREENW	1200
# define _SCREENH	640

# define _TEX_NBR	4
# define _TEX_SIZE	64

# define _XSIDE	0
# define _YSIDE	1
# define _SPEED	0.015

typedef struct	s_color
{
	int	r;
	int	g;
	int	b;
	int	color;
}				t_color;

typedef struct	s_coord
{
	double	x;
	double	y;
}				t_coord;

typedef struct	s_img
{
	void	*mlx_img;
	int		*addr;
	int		bpp;
	int		line_len;
	int		endian;
	int		x;
	int		y;
}				t_img;

typedef struct	s_mlx
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_img	canvas;
	int		screenw;
	int		screenh;
}				t_mlx;

enum	e_move
{
	_P1_UP = 1,
	_P1_DOWN = 2,
	_P1_LEFT = 4,
	_P1_RIGHT = 8,
	_CAM_LEFT = 16,
	_CAM_RIGHT = 32
};

typedef struct	s_player
{
	t_coord	dir;
	double	speed;
	int		move;
	t_coord	pos;
	t_coord	cam_plane;
}				t_player;

typedef struct	s_c3d
{
	char		**map;
	int			**buffer;
	int			*textures[_TEX_NBR];
	char		*tex_paths[_TEX_NBR];
	t_mlx		mlx;
	t_player	player;
	t_color		floor;
	t_color		ceiling;
}				t_c3d;

typedef struct	s_ray
{
	double	dirx;
	double	diry;
	double	delta_distx;
	double	delta_disty;
	double	side_distx;
	double	side_disty;
	double	perp_walldist;
	int		mapx;
	int		mapy;
	int		stepx;
	int		stepy;
	int		side;
}				t_ray;

typedef struct	s_line
{
	int		lineheight;
	int		draw_start;
	int		draw_end;
	int		orientation;
}				t_line;

void	c3d_draw_on_screen(t_c3d *env, t_mlx *mlx);
void	c3d_draw_wall_texture_on_line(t_c3d *env, t_line *tex_line, t_ray ray, int x);
void	c3d_execute_raycasting(t_c3d *env);
void	*c3d_memset(void *s, int c, size_t n);
void	c3d_handle_keyhooks(t_c3d *env);
void	c3d_init(t_c3d *env, char *argv[]);
void	c3d_init_window(t_c3d *env, t_mlx *mlx);

/************** free	*****************/
void	*c3d_free(void *ptr);
void	c3d_free_array_of_char_pointers(char *array[]);
void	c3d_free_array_of_int_pointers(int *array[]);
void	c3d_free_pointers_from_char_array(char *array[]);
void	c3d_free_pointers_from_int_array(int *array[]);

/************** parsing	*****************/
void	__c3d_parse_map(t_c3d *env, t_player *player, char **argv);
int		__check_file(char **av, int	*fd, t_parser *parser);
int		__fill_parser_buf(t_parser *parser, int fd);
int		__check_type(char *line, int *type);
void	__parse_line(t_parser *parser, char *line);
int		__add_in_err_buf(t_parser *parser, int error_type);
void	c3d_parse_map_exit(t_parser *parser);
int		c3d_add_to_env(t_parser *parser, t_c3d *env);
int		c3d_add_color_to_env(t_parser *parser, t_c3d *env);
int		c3d_add_map_to_env(t_parser *parser, t_c3d *env);
int		c3d_map_to_env(t_parser *parser, t_c3d *env);

int		__add_info_err_buf(t_parser *parser, int type, int error_num);


//void	c3d_load_textures(t_c3d *env, t_parser *parsing, t_mlx *mlx);

void	__visual_env_rgb(t_c3d *env);
void	__visual_env_tex_path(t_c3d *env);

int			ft_strlen(char *str);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_strchr_b(const char *s, int c);
long int	ft_atol(const char *str);
int			ft_isdigit(int c);

int		c3d_exit(t_c3d *env, int err_code);

void	c3d_check_obstacles_and_move_up(char **map, t_player *player);
void	c3d_check_obstacles_and_move_down(char **map, t_player *player);
void	c3d_check_obstacles_and_move_left(char **map, t_player *player);
void	c3d_check_obstacles_and_move_right(char **map, t_player *player);
void	c3d_look_left(t_player *p);
void	c3d_look_right(t_player *p);

void	c3d_render_line_to_buffer(t_c3d *env, t_line line, t_ray ray, int x);

/************** free	*****************/
int	c3d_exit_game(t_c3d *env, t_mlx *mlx);
int	c3d_exit_init(t_c3d *env, int err_code);

#endif
