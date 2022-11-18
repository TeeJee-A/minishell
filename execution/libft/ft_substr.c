/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataji <ataji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 21:20:12 by ataji             #+#    #+#             */
/*   Updated: 2022/11/18 11:00:47 by ataji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*my_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*str;

	i = 0;
	if (!s)
		return (NULL);
	if (start < my_strlen(s))
	{
		if (my_strlen(s) < len)
			len = my_strlen(s);
		str = ft_malloc((len + 1) * sizeof(char));
		while (i < len)
			str[i++] = s[start++];
	}
	else
		str = ft_malloc(1);
	str[i] = '\0';
	return (str);
}
