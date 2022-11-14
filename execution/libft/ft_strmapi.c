/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataji <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 19:57:32 by ataji             #+#    #+#             */
/*   Updated: 2021/12/01 22:39:12 by ataji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*str;

	if (!s)
		return (NULL);
	i = ft_strlen(s);
	str = (char *)malloc(i + 1);
	if (!str)
		return (NULL);
	str[i--] = '\0';
	while (i >= 0)
	{
		str[i] = f(i, s[i]);
		i--;
	}
	return (str);
}
