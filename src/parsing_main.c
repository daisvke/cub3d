/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/28 19:03:37 by lchan             #+#    #+#             */
/*   Updated: 2022/08/29 14:58:54 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	__strlen(char *str)
{
	char	*tmp;

	tmp = str;
	while (*tmp)
		tmp++;
	return (tmp - str);
}

void	__putstr_err(const char *err_message)
{
	write (STDERR_FILENO, err_message, __strlen((char *)err_message));
}

void	__print_err(int	err)
{
	const char	*err_msg[] = {
	[ERR_EXTENTION] = "unvalid extention\n",
	[ERR_FOLDER] = "expecting : file.cut, received : folder.cub\n",
	[ERR_CHMOD] = "access denied\n",
	[ERR_PATH] = "path seems incorrect\n",
	};
	int			n_bit;

	if (err)
	{
		n_bit = -1;
		__putstr_err("list of error: \n");
		while (++n_bit < NBR_PARSING_ERR )
			if ((err >> n_bit) & 1)
				__putstr_err(err_msg[n_bit]);
	}
}

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

void	__c3d_parse_map(t_c3d *env, t_player *player, char **argv)
{
	int	err;
	int	fd;
	(void) env;
	(void) player;

	err = 0;
	fd = -1;
	err += __check_file(argv + 1, &fd);
	//err += __check_map(env, env->player, fd);
	if (err)
	{
		printf("err flag = %d\n", err);
		__print_err(err);
		//__free_parsing(env);
		exit(err);
	}
}
