#ifndef CUB3D_H
# define CUB3D_H

# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <stdbool.h>
# include <fcntl.h>
# include <X11/keysym.h>
# include <mlx.h>
# include <X11/X.h>

# define _TITLE		"cub3d"
# define _SCREENW	640
# define _SCREENH	480

# define _CAM_PLANE_X	0
# define _CAM_PLANE_Y	0.66

# define _XSIDE	0
# define _YSIDE	1

typedef struct	s_coord
{
	int	x;
	int	y;
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

typedef struct	s_player
{
	t_coord	dir;
	t_coord	pos;
}				t_player;

typedef struct	s_c3d
{
	char		**map;
	int			**buffer;
	double		*zbuffer;
	t_mlx		mlx;	
	t_player	player;
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
	double	pos;
	t_coord	dir;
	int		lineheight;
	int		draw_start;
	int		draw_end;
}				t_line;

void	c3d_draw_on_screen(t_c3d *env, t_mlx *mlx);
void	c3d_execute_raycasting(t_c3d *env);
void	*ft_memset(void *s, int c, size_t n);
void	c3d_handle_keyhooks(t_c3d *env);
void	c3d_init(t_c3d *env, char *argv[]);
int		c3d_exit(t_c3d *env, int errno);
void	c3d_render_line_to_buffer(t_c3d *env, t_line line, t_ray ray, int x);

#endif
