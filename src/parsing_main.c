/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 19:03:37 by lchan             #+#    #+#             */
/*   Updated: 2022/09/01 16:34:01 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
void	__free_parsing(t_c3d *env)
{
	char	**tmp;

	if (env->map)
	{
		tmp = env->map;
		while (*tmp)
		{
			free(*tmp);
			tmp++;
		}
		free(env->map);
		env->map = NULL;
	}
}
*/

void	__visual_parser_buf(t_parser *parser)
{
	int	i = -1;

	const char	*type_tab[] = {
	[TYPE_NO] = "NO", [TYPE_SO] = "SO",
	[TYPE_WE] = "WE", [TYPE_EA] = "EA", [TYPE_F] = "F",
	[TYPE_C] = "C",
	};

	const char	*map_err_tab[] = {
	[ERR_EMPTY_MAP] = "ERR_EMPTY_MAP", [ERR_MISSING_INFO] = "ERR_MISSING_INFO",
	[ERR_GIBBERISH] = "ERR_GIBBERISH", [ERR_TEXTURE_KEY_MISSING] = "ERR_TEXTURE_KEY_MISSING", [ERR_TEXTURE_MULTIDEF] = "ERR_TEXTURE_MULTIDEF",
	[ERR_TEXTURE_PATH] = "ERR_TEXTURE_PATH", [ERR_TEXTURE_PATH_LENGH] = "ERR_TEXTURE_PATH_LENGH",
	[ERR_FC_OVERFLOW] = "ERR_FC_OVERFLOW",
	[ERR_FC_KEY_MISSING] = "ERR_FC_KEY_MISSING", [ERR_FC_MULTIDEF] = "ERR_FC_MULTIDEF", [ERR_FC_COLOR_FORM] = "ERR_FC_COLOR_FORM",
	[ERR_MAP_UNVALID_CHAR] = "ERR_MAP_UNVALID_CHAR", [ERR_MAP_CHARACTER] = "ERR_MAP_CHARACTER", [ERR_MAP_BORDERS] = "ERR_MAP_BORDERS",
	[ERR_MAP_TOO_BIG] = "ERR_MAP_TOO_BIG",
	};

	printf("gnl_cnt = %d\n", parser->gnl_cnt);
	while (++i <= TYPE_C)
		printf("map_buf[%s] = %s\n", type_tab[i], parser->info_buf[i]);
	i = -1;
	printf("MAP = \n");
	while (++i < parser->map_buf_index)
		printf("%s", parser->map_buf[i]);
	i = -1;
	printf("err_found :\n\n");
	while (++i < parser->err_buf_index)
		printf("line : %d : %s\n", parser->err_buf[i][0], map_err_tab[parser->err_buf[i][1]]);
}







void	__putstr_err(const char *err_message)
{
	write (STDERR_FILENO, err_message, ft_strlen((char *)err_message));
}

void	__print_err_exit(int err)
{
	int			n_bit;
	const char	*err_msg[] = {
	[ERR_NO_FILE] = MESS_NO_FILE, [ERR_EXTENTION] = MESS_EXTENTION,
	[ERR_FOLDER] = MESS_FOLDER, [ERR_CHMOD] = MESS_CHMOD, [ERR_PATH] = MESS_PATH,
	};

	n_bit = -1;
	__putstr_err(MESS_ERR_LST);
	while (++n_bit < NBR_PARSING_ERR )
		if ((err >> n_bit) & 1)
			__putstr_err(err_msg[n_bit]);
	exit(err);
}

/*****************************
 * __check_file opens the file
 * __check_map closes the file
 * ***************************/
void	__c3d_parse_map(t_c3d *env, t_player *player, char **argv)
{
	int	err;
	int	fd;
	t_parser	parser;
	(void) env;
	(void) player;

	err = 0;
	fd = -1;
	if (__check_file(argv + 1, &fd))
		__print_err_exit(err);
	__fill_parser_buf(&parser, fd);
	__visual_parser_buf(&parser);
	// if (__check_info_validity(parser))
	// 		__add_info_to_env(parser, env);
/*
	if (err)
	{
		printf("err flag = %d\n", err);
	}*/
}
