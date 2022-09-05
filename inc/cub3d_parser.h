/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_parser.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 17:10:51 by lchan             #+#    #+#             */
/*   Updated: 2022/09/05 19:51:16 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_PARSER_H
# define CUB3D_PARSER_H

# define MAP_CHAR " 01SEWN"
# define MAP_ORIENT_CHAR "SEWN"
# define FOUND 0
# define COLOR_MAX_LEN 11
# define NBR_PARSING_ERR 11 // not sure it is usefull anymore
# define PARSER_BUFFER_SIZE 1024
# define DIR 1.0
# define CAM_PLANE 0.66
# define X_ADJUST 0.5
# define Y_ADJUST 0.5

# define MS_MLX_INIT "1: mlx_init failed!\n"
# define MS_MLX_RESOLUTION "2: the screen resolution is too low!\n"
# define MS_MLX_NEW_IMG "3: mlx_new_image failed!\n"
# define MS_MLX_NEW_WIN "4: mlx_new_window failed!\n"

# define MS_ERR_LST "list of errors: \n"
# define MS_BLK_ERR "blocking error"
# define MS_NO_FILE "path to map is missing\n"
# define MS_EXTENTION "invalid extention\n"
# define MS_FOLDER "expecting : file.cut but received : directory.cub\n"
# define MS_CHMOD "access denied\n"
# define MS_PATH "path seems incorrect\n"
# define MS_EMPTY_FILE "	: map seems to be empty\n"
# define MS_TX_KEY_MISS "	: one or more texture path missing\n"
# define MS_TX_PATH "	: texture path seems incorrect\n"
# define MS_TX_PATH_LENGH "	: path too long\n"
# define MS_FC_OVERFLOW "	: colors value can not exceed 255\n"
# define MS_FC_KEY_MISS "	: one or more color missing\n"
# define MS_FC_FORM "	: expected color format : F/C 255.255.255\n"
# define MS_MP_MISPLACED "	: map misplaced\n"
# define MS_MP_TOO_SMALL "	: no map / map is too small\n"
# define MS_MP_NO_PLAYER "	: a player is needed in the map\n"
# define MS_MP_MULTI_PLAYER "	: found more than one player in the map\n"
# define MS_MP_CUTTED "	: according to the subject the map has to be in one piece\n"
# define MS_MP_BORDERS "	: incorrect map borders\n"
# define MS_MP_TOO_BIG "	: map is too big\n"
# define MS_MP_UNABLE_TO_CPY "	: impossible to cpy map\n"
# define MS_GIBBER "	: found gibberish in infile\n"
# define MS_FC_MULTIDEF "	: re-definition of colors ignored\n"
# define MS_TX_MULTIDEF "	: re-definition of texture ignored\n"

enum	e_file_err
{
	/********************	ERR_FILE*/
	ERR_NO_FILE,			//bit 0/32
	ERR_EXTENTION,			//bit 1/32
	ERR_FOLDER,				//bit 2/32
	ERR_CHMOD,				//bit 3/32
	ERR_PATH,				//bit 4/32
};

enum	e_map_err{
	ERR_EMPTY_FILE,
	/********************	ERR_TEXTURE*/
	ERR_TX_KEY_MISS,	//not sure
	ERR_TX_PATH,
	ERR_TX_PATH_LENGH,
	/********************	ERR_FC_C*/
	ERR_FC_OVERFLOW,
	ERR_FC_KEY_MISS,
	ERR_FC_FORM,					//expected color form : F/C 255.255.255
	/********************	ERR_MAP*/
	ERR_MP_MISPLACED,
	ERR_MP_TOO_SMALL,
	ERR_MP_NO_PLAYER,
	ERR_MP_MULTI_PLAYER,
	ERR_MP_CUTTED,
	ERR_MP_BORDERS,
	ERR_MP_TOO_BIG,					//MP has more than 1024 line
	ERR_MP_UNABLE_TO_CPY,
	/*******************	non_blocking_err*/
	ERR_GIBBER,
	ERR_FC_MULTIDEF,
	ERR_TX_MULTIDEF,
};

enum	e_line_type{
	TYPE_NO,
	TYPE_SO,
	TYPE_WE,
	TYPE_EA,
	TYPE_F,
	TYPE_C,
	TYPE_MAP,
	TYPE_ERR,		//line start by unvalide chars
	TYPE_USELESS,	//line composed of space and/or \n
	TYPE_EOF,
};

enum	e_err_buf_index{
	LINE_NBR,
	ERROR_CODE,
};

enum	e_tab_free_opt{
	NO_INDEX,
	WITH_INDEX,
};

typedef struct s_parser
{
	char	*line;				//current gnl line;
	int		gnl_cnt;			//nbr of gnl calls aka line nbr at each call
	int		map_max_x;
	int		map_max_y;
	int		type;				//type of line; e_line_type
	char	info_buf[6][PATH_MAX + 2];
	int		info_buf_line[6];
	char	*map_buf[PARSER_BUFFER_SIZE];
	int		map_line_buf[PARSER_BUFFER_SIZE];	//save gnl of type map
	int		err_buf[PARSER_BUFFER_SIZE][2];	//save line numbers of time error
	int		info_buf_flag;
	int		map_buf_index;		//is also the size of the map
	int		err_buf_index;
	int		blocking_err_flag;
}t_parser;

#endif
