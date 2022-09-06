/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser0_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 19:03:37 by lchan             #+#    #+#             */
/*   Updated: 2022/09/06 18:39:23 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	c3d_update_err_flag(t_parser *parser, int err_nbr)
{
	parser->blocking_err_flag |= (1 << err_nbr);
	return (parser->blocking_err_flag);
}

char	**c3d_freetab_index(char **tab, int index, int opt)
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
 * c3d_check_file opens the file
 * c3d_check_map closes the file
 * ***************************/
void	c3d_c3d_parse_map(t_c3d *env, char **argv)
{
	int			fd;
	t_parser	parser;

	fd = -1;
	c3d_memset(&parser, 0, sizeof(t_parser));
	if (c3d_check_file(argv + 1, &fd, &parser))
		c3d_print_file_err_exit(parser.blocking_err_flag);
	else if (c3d_fill_parser_buf(&parser, fd))
		c3d_print_parse_err_exit(&parser, env);
	else if (c3d_init(env))
		c3d_add_to_env_exit(&parser, env);
	else if (c3d_add_to_env(&parser, env))
		c3d_print_parse_err_exit(&parser, env);
	c3d_freetab_index(parser.map_buf, parser.map_buf_index, WITH_INDEX);
}
