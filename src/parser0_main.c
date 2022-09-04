/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser0_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 19:03:37 by lchan             #+#    #+#             */
/*   Updated: 2022/09/04 21:56:04 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	__visual_parser_buf(t_parser *parser)
{
	int	i = -1;

	const char	*type_tab[] = {
	[TYPE_NO] = "NO", [TYPE_SO] = "SO",
	[TYPE_WE] = "WE", [TYPE_EA] = "EA", [TYPE_F] = "F",
	[TYPE_C] = "C",
	};

	printf("info_buf_flag = %d\n", parser->info_buf_flag);
	printf("gnl_cnt = %d\n", parser->gnl_cnt);
	while (++i <= TYPE_C)
		printf("map_buf[%s] = %s\n", type_tab[i], parser->info_buf[i]);
	i = -1;
	printf("MAP = \n");
	while (++i < parser->map_buf_index)
		printf("%s", parser->map_buf[i]);
	// i = -1;
	// printf("err_found :\n");
	// while (++i < parser->err_buf_index)
	// 	printf("line : %d : %s\n", parser->err_buf[i][0], map_err_tab[parser->err_buf[i][1]]);
// 	i = -1;
// 	printf("blocking errors: \n");
// 	while (++i <=  ERR_MAP_TOO_BIG)
// 		if ((parser->blocking_err_flag >> i) & 1)
// 			printf("%s\n", (map_err_tab[i]));
}

void	__putstr_err(const char *err_message)
{
	write (STDERR_FILENO, err_message, ft_strlen((char *)err_message));
}

void	__print_file_err_exit(int err)
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

void	__print_parser_buf_err_exit(t_parser *parser)
{
	int	i;
	const char	*map_err_tab[] = {
	[ERR_EMPTY_FILE] = "ERR_EMPTY_FILE",
//	[ERR_MISSING_MAP] = "ERR_MISSING_MAP",
	[ERR_MAP_MISPLACED] = "ERR_MAP_MISPLACED",
	[ERR_GIBBERISH] = "ERR_GIBBERISH",
	[ERR_TEXTURE_KEY_MISSING] = "ERR_TEXTURE_KEY_MISSING",
	[ERR_TEXTURE_MULTIDEF] = "ERR_TEXTURE_MULTIDEF",
	[ERR_TEXTURE_PATH] = "ERR_TEXTURE_PATH",
	[ERR_TEXTURE_PATH_LENGH] = "ERR_TEXTURE_PATH_LENGH",
	[ERR_FC_OVERFLOW] = "ERR_FC_OVERFLOW",
	[ERR_FC_KEY_MISSING] = "ERR_FC_KEY_MISSING",
	[ERR_FC_MULTIDEF] = "ERR_FC_MULTIDEF",
	[ERR_FC_COLOR_FORM] = "ERR_FC_COLOR_FORM",
	[ERR_MAP_TOO_SMALL] = "ERR_MAP_TOO_SMALL",
	[ERR_MAP_NO_PLAYER] = "ERR_MAP_NO_PLAYER",
	[ERR_MAP_MULTI_PLAYER] = "ERR_MAP_MULTI_PLAYER",
	[ERR_MAP_UNVALID_CHAR] = "ERR_MAP_UNVALID_CHAR",
	[ERR_MAP_BORDERS] = "ERR_MAP_BORDERS",
	[ERR_MAP_TOO_BIG] = "ERR_MAP_TOO_BIG",
	};

	if (parser->blocking_err_flag)
	{
		i = -1;
		printf("err_found :\n");
		while (++i < parser->err_buf_index)
			printf("line : %d : %s\n", parser->err_buf[i][0], map_err_tab[parser->err_buf[i][1]]);
		i = -1;
		printf("blocking errors list: \n");
		while (++i <=  ERR_MAP_TOO_BIG)
			if ((parser->blocking_err_flag >> i) & 1)
				printf("%s\n", (map_err_tab[i]));
		if (parser->blocking_err_flag)
			c3d_parse_map_exit(parser);
	}
}

char	**__freetab_index(char **tab, int index, int opt)
{
	int	i;

	i = -1;
	if (opt)
	{
		while (++i < index)
			free(tab[i]);
	}
	else
	{
		while (tab[++i])
			free(tab[i]);
		free(tab);
	}
	return (NULL);
}

/*****************************
 * __check_file opens the file
 * __check_map closes the file
 * ***************************/
void	__c3d_parse_map(t_c3d *env, t_player *player, char **argv)
{
	int	fd;
	t_parser	parser;
	(void) player;

	fd = -1;
	c3d_memset(&parser, 0, sizeof(t_parser));
	if (__check_file(argv + 1, &fd, &parser))
		__print_file_err_exit(parser.blocking_err_flag);
	/************ filling parser : need to free only parser*/


	__fill_parser_buf(&parser, fd);
	//__visual_parser_buf(&parser);
	//__freetab_index(parser->map_buf, parser->map_buf_index, WITH_INDEX); //to free parser_map
	__print_parser_buf_err_exit(&parser);

	/************ cpy into env : need to free parser and env*/
	c3d_add_to_env(&parser, env);
	__visual_env_global(env);
	__print_parser_buf_err_exit(&parser);
	__freetab_index(parser.map_buf, parser.map_buf_index, WITH_INDEX);
		//need to free parser + env;


	//c3d_parse_map_exit(&parser);





	// 		__add_info_to_env(parser, env);
/*
	if (err)
	{
		printf("err flag = %d\n", err);
	}*/
}


//Samedi 3 septembre : la map doit etre a la fin du ficher d'entre.
