/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser6_add_to_env.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/03 14:34:45 by lchan             #+#    #+#             */
/*   Updated: 2022/09/03 21:47:49 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


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
		__add_info_err_buf(parser, type, ERR_FC_COLOR_FORM);
	return (num_flag);
}

int	c3d_add_color_to_env(t_parser *parser, t_c3d *env)
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
