/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataji <ataji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 19:57:32 by ataji             #+#    #+#             */
/*   Updated: 2022/11/18 11:00:10 by ataji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*my_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*str;

	if (!s)
		return (NULL);
	i = my_strlen(s);
	str = ft_malloc(i + 1);
	str[i--] = '\0';
	while (i >= 0)
	{
		str[i] = f(i, s[i]);
		i--;
	}
	return (str);
}
