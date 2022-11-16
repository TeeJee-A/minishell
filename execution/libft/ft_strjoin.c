/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataji <ataji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 15:20:08 by ataji             #+#    #+#             */
/*   Updated: 2022/11/15 22:48:04 by ataji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*my_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	size_t	sl1;
	size_t	sl2;
	char	*str;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	sl1 = my_strlen (s1);
	sl2 = my_strlen (s2);
	str = (char *)malloc((sl1 + sl2 + 1) * sizeof(char));
	if (!str)
		return (NULL);
	while (i < sl1)
	{
		str[i] = s1[i];
		i++;
	}
	while (j < sl2)
		str[i++] = s2[j++];
	str[i] = '\0';
	return (str);
}
