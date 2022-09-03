/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser5_add_to_env.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 19:42:12 by lchan             #+#    #+#             */
/*   Updated: 2022/09/03 17:15:03 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	__add_info_err_buf(t_parser *parser, int type, int error_num)
{
	parser->blocking_err_flag |= (1<<error_num);
	parser->err_buf[parser->err_buf_index][LINE_NBR] = parser->info_buf_line[type];
	parser->err_buf[parser->err_buf_index][ERROR_CODE] = error_num;
	parser->err_buf_index++;
	return (-1);
}

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

int	c3d_add_path_to_env(t_parser *parser, t_c3d *env)
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

int	c3d_add_to_env(t_parser *parser, t_c3d *env)
{
	c3d_add_path_to_env(parser, env);
	c3d_add_color_to_env(parser, env);
	c3d_add_map_to_env(parser,env);
	return (parser->blocking_err_flag);
}
