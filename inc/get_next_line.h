/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 14:38:47 by lchan             #+#    #+#             */
/*   Updated: 2022/08/30 16:13:52 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <stdio.h>

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>

typedef struct s_list
{
	int				fd;
	char			*content;
	char			buff[BUFFER_SIZE + 1];
	struct s_list	*next;
}t_list;

//get_next_line_utils.c
size_t	c3d_strlen_opt_newline(char *str, int opt_newline);
char	*c3d_strjoinfree_content(t_list *nod);
t_list	*c3d_struct_init(int fd);
t_list	*c3d_lst_init_addback(t_list **head, int fd);

//get_next_line.c
void	c3d_rebuild_buff(t_list *nod);
void	gnl_build_content(t_list **nod, int fd);
char	*get_next_line(int fd);

#endif
