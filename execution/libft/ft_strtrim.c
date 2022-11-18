/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataji <ataji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 21:54:40 by ataji             #+#    #+#             */
/*   Updated: 2022/11/18 11:00:28 by ataji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	my_search(const char *s, char c)
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

char	*my_strtrim(char const *s1, char const *set)
{
	int		sl;
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	if (!s1 || !set)
		return (NULL);
	sl = my_strlen(s1);
	sl--;
	while (s1 && (my_search(set, s1[i]) == 1))
		i++;
	while (sl >= 0 && (my_search(set, s1[sl]) == 1))
		sl--;
	if (sl - i < 0)
		return (my_strdup(""));
	str = ft_malloc(sl - i + 2 * sizeof(char));
	while (i <= sl)
		str[j++] = s1[i++];
	str[j] = '\0';
	return (str);
}
