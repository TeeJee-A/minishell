/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataji <ataji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 21:20:12 by ataji             #+#    #+#             */
/*   Updated: 2022/11/15 22:49:11 by ataji            ###   ########.fr       */
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
		str = (char *)malloc((len + 1) * sizeof(char));
		if (!str)
			return (NULL);
		while (i < len)
			str[i++] = s[start++];
	}
	else
		str = malloc(1);
	str[i] = '\0';
	return (str);
}
