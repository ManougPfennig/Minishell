/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mapfenni <mapfenni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 17:52:35 by mapfenni          #+#    #+#             */
/*   Updated: 2024/01/14 20:50:56 by mapfenni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(char *src)
{
	int		i;
	char	*dest;
	int		src_size;

	if (src == NULL)
		return (NULL);
	src_size = 0;
	while (src && src[src_size] != '\0')
		src_size++;
	dest = (char *)malloc((src_size + 1) * sizeof(char));
	if (!dest)
		return (NULL);
	i = 0;
	while (src && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	if (dest == NULL)
		return (0);
	if (src && src[i] == '\0')
		dest[i] = '\0';
	return (dest);
}

/*#include <stdio.h>
int main()
{
	char *src = "123456789";
	char *bam = ft_strdup(src);
	printf("%s\n", bam);
}*/
