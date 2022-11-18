/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataji <ataji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 18:43:14 by ataji             #+#    #+#             */
/*   Updated: 2022/11/15 22:46:03 by ataji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils_char_str.h"

void	*my_memchr(const void *s, int c, size_t n)
{
	unsigned char	k;
	unsigned char	*str;
	size_t			i;

	k = (unsigned char)c;
	str = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (str[i] == k)
			return (str + i);
		i++;
	}
	return (NULL);
}
