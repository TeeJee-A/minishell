/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataji <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 21:54:40 by ataji             #+#    #+#             */
/*   Updated: 2021/12/01 22:59:04 by ataji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_search(const char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			return (1);
		i++;
	}
	return (0);
}	

char	*ft_strtrim(char const *s1, char const *set)
{
	int		sl;
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	if (!s1 || !set)
		return (NULL);
	sl = ft_strlen(s1);
	sl--;
	while (s1 && (ft_search(set, s1[i]) == 1))
		i++;
	while (sl >= 0 && (ft_search(set, s1[sl]) == 1))
		sl--;
	if (sl - i < 0)
		return (ft_strdup(""));
	str = (char *)malloc(sl - i + 2 * sizeof(char));
	if (!str)
		return (NULL);
	while (i <= sl)
		str[j++] = s1[i++];
	str[j] = '\0';
	return (str);
}
