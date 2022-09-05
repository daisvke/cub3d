/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser0_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 19:03:37 by lchan             #+#    #+#             */
/*   Updated: 2022/09/05 16:18:34 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	update_err_flag(t_parser *parser, int err_nbr)
{
	parser->blocking_err_flag |= (1<<err_nbr);
	return(parser->blocking_err_flag);
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
	else if (__fill_parser_buf(&parser, fd))
		__print_parse_err_exit(&parser);
	else if (c3d_add_to_env(&parser, env))
		__print_parse_err_exit(&parser);
	__freetab_index(parser.map_buf, parser.map_buf_index, WITH_INDEX);
}
