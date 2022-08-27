#include "cub3d.h"

void	*ft_memset(void *s, int c, size_t n)
{
	char	*str;
	size_t	i;

	str = s;
	i = 0;
	while (i < n)
	{
		*(str + i) = c;
		++i;
	}
	return (s);
}
