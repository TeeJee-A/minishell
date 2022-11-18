/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataji <ataji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 17:05:49 by ataji             #+#    #+#             */
/*   Updated: 2022/11/15 22:46:36 by ataji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils_char_str.h"

void	*my_memset(void *b, int c, size_t len)
{
	unsigned char	*str;

	str = b;
	while (len > 0)
	{
		len--;
		*str = c;
		str++;
	}
	return (b);
}
