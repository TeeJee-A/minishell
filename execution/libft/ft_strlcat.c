/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataji <ataji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 17:02:56 by ataji             #+#    #+#             */
/*   Updated: 2022/11/17 20:51:54 by ataji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils_char_str.h"

size_t	my_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (dst[i] != '\0' && i < dstsize)
		i++;
	while (src[j] != '\0' && i + j < dstsize - 1 && dstsize != 0)
	{
		dst[i + j] = src[j];
		j++;
		dst[i + j] = '\0';
	}
	while (src[j] != '\0')
		j++;
	if (dstsize <= i)
		return (j + dstsize);
	return (j + i);
}
