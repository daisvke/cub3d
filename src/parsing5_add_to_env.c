/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing5_add_to_env.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 19:42:12 by lchan             #+#    #+#             */
/*   Updated: 2022/09/03 14:29:07 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


int	c3d_load_texture(t_c3d *env, t_mlx *mlx, int i, t_img *img)
{
	int		*tex;
	char	*path;
	int		x;
	int		y;

	tex = env->textures[i];
	path = env->tex_paths[i];
	img->mlx_img = mlx_xpm_file_to_image(mlx->mlx_ptr, path, &img->x, &img->y);
	if (!img->mlx_img)
		return -1;
	img->addr = (int *)mlx_get_data_addr(img->mlx_img, &img->bpp, &img->line_len, &img->endian);
	y = 0;
	while (y < img->y)
	{
		x = 0;
		while (x < img->x)
		{
			tex[img->x * y + x] = img->addr[img->x * y + x];
			++x;
		}
		++y;
	}
	return (0);
}

int	c3d_load_textures(t_c3d *env, t_mlx *mlx)
{
	t_img	img[_TEX_NBR];
	int		i;
	int		j;

	i = -1;
	j = 0;
	while (++i < _TEX_NBR)
		if (c3d_load_texture(env, mlx, i, &img[i]))
			break;
	while (j < i)
	{
		mlx_destroy_image(mlx->mlx_ptr, img[j].mlx_img);
		j++;
	}
	if (i != _TEX_NBR)
		return (i);
	return (0);
}

int	__add_info_err_buf(t_parser *parser, int type, int error_num)
{
	parser->blocking_err_flag |= (1<<error_num);
	parser->err_buf[parser->err_buf_index][LINE_NBR] = parser->info_buf_line[type];
	parser->err_buf[parser->err_buf_index][ERROR_CODE] = error_num;
	parser->err_buf_index++;
	return (-1);
}

int	__add_path_to_env(t_parser *parser, t_c3d *env)
{
	int		i;
	int		load_text_ret;

	i = -1;
	while (++i < _TEX_NBR)
		env->tex_paths[i] = parser->info_buf[i];
	load_text_ret = c3d_load_textures(env, &(env->mlx));
	if (load_text_ret)
		return (__add_info_err_buf(parser, load_text_ret, ERR_TEXTURE_PATH));
	return (0);
}









int	c3d_convert_rgb_to_int(t_color color)
{
	int	val;

	val = color.r;
	val = (val << 8) + color.g;
	val = (val << 8) + color.b;
	return (val);
}

void	__send_color_to_env(long long rgb[3], t_c3d *env, int type)
{
	if (type == TYPE_F)
	{
		env->floor.r = (int)rgb[0];
		env->floor.g = (int)rgb[1];
		env->floor.b = (int)rgb[2];
		env->floor.color = c3d_convert_rgb_to_int(env->floor);
	}
	else
	{
		env->ceiling.r = (int)rgb[0];
		env->ceiling.g = (int)rgb[1];
		env->ceiling.b = (int)rgb[2];
		env->ceiling.color = c3d_convert_rgb_to_int(env->ceiling);
	}
}

int	__conv_and_add_to_env(t_parser *parser, t_c3d *env, int type)
{
	long long	rgb[3];
	int			rgb_index;
	int			info_index;
	char 		*buf;

	rgb_index = -1;
	info_index = 0;
	buf = &(parser->info_buf[type][info_index]);
	c3d_memset(&rgb, 0, sizeof(rgb));
	if (ft_strlen(buf) > 11)
		return(__add_info_err_buf(parser, type, ERR_FC_OVERFLOW));
	while (++rgb_index < 3)
	{
		rgb[rgb_index] = ft_atol(buf);
		if (rgb[rgb_index] > 255)
			return (__add_info_err_buf(parser, type, ERR_FC_OVERFLOW));
		while(*buf >= '0' && *buf<= '9')
			buf++;
		buf++;
	}
	__send_color_to_env(rgb, env, type);
	return (0);
}

int	__recheck_color_form(t_parser *parser, char *color, int type)
{
	int	num_flag;

	num_flag = 3;
	while (*color)
	{
		if (ft_isdigit(*color))
			num_flag--;
		while (*color && ft_isdigit(*color))
			color++;
		if (*color == ',')
			color++;
	}
	if (num_flag)
		__add_info_err_buf(parser, type, ERR_FC_OVERFLOW);
	return (num_flag);
}

int	__add_color_to_env(t_parser *parser, t_c3d *env)
{
	int	ret;

	ret = 0;
	ret += __recheck_color_form(parser, parser->info_buf[TYPE_F], TYPE_F);
	ret += __recheck_color_form(parser, parser->info_buf[TYPE_C], TYPE_C);
	if (!ret)
	{
		ret +=__conv_and_add_to_env(parser, env, TYPE_F);
		ret +=__conv_and_add_to_env(parser, env, TYPE_C);
	}
	return (ret);
}

int	__add_to_env(t_parser *parser, t_c3d *env)
{
	(void) env;
	__add_path_to_env(parser, env);
	__add_color_to_env(parser, env);
	//__add_map_to_env(parser,env);
	return (parser->blocking_err_flag);
}