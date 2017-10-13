/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sasiedu <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/22 23:04:51 by sasiedu           #+#    #+#             */
/*   Updated: 2016/08/16 12:27:30 by sasiedu          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *restrict dst, const void *restrict src, int c, \
		size_t n)
{
	size_t	i;
	unsigned char	*a;
	unsigned char	*b;

	a = (unsigned char *)dst;
	b = (unsigned char *)src;
	if (src == NULL || dst == NULL || n == 0)
		return (NULL);
	i = 0;
	while (b[i] && i < n)
	{
		if (b[i] == (unsigned char)c)
			return (&dst[i + 1]);
		a[i] = b[i];
		i++;
	}
	if (b[i] == (unsigned char)c)
		return (&dst[i + 1]);
	return (NULL);
}
