/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing7_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lchan <lchan@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/31 12:07:07 by lchan             #+#    #+#             */
/*   Updated: 2022/09/03 15:44:21 by lchan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	ft_strlen(char *str)
{
	char	*tmp;

	tmp = str;
	while (*tmp)
		tmp++;
	return (tmp - str);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		if (s1[i] == '\0' && s2[i] == '\0')
			return (0);
		i++;
	}
	return (0);
}

int	ft_strchr_b(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (unsigned char) c)
			return (0);
		i++;
	}
	return (-1);
}

// char	*ft_strdup(char *s1)
// {
// 	size_t	len;
// 	char	*dup;

// 	if (s1)
// 		len = ft_strlen(s1);
// 	else
// 		len = 0;
// 	dup = (char *)malloc((len + 1) * sizeof(char));
// 	if (!dup)
// 		return (0);
// 	while (s1 && *s1 != '\0')
// 	{
// 		*dup = *s1;
// 		s1++;
// 		dup++;
// 	}
// 	*dup = '\0';
// 	return (dup - len);
// }

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

long int	ft_atol(const char *str)
{
	int			sign;
	long int	result;

	sign = 1;
	result = 0;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if ((*str == '+' || *str == '-') && str++)
		if (*(str - 1) == '-')
			sign = -sign;
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + *str - '0';
		str++;
	}
	return (result * (long int)sign);
}