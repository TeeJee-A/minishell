/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataji <ataji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/07 15:27:49 by ataji             #+#    #+#             */
/*   Updated: 2022/11/15 22:46:14 by ataji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*my_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*str;
	unsigned char	*ptr;
	size_t			i;

	str = (unsigned char *)src;
	ptr = (unsigned char *)dst;
	i = 0;
	if (!dst && !src)
		return (NULL);
	while (i < n)
	{
		ptr[i] = str[i];
		i++;
	}
	return (ptr);
}
