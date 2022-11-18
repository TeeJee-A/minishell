/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataji <ataji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 22:54:39 by kfaouzi           #+#    #+#             */
/*   Updated: 2022/11/18 11:02:55 by ataji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils_char_str.h"

char	*ft_substr(char *s, unsigned int start, size_t len)
{
	size_t	str_len;
	size_t	i;
	char	*new;

	i = 0;
	if (!s)
		return (NULL);
	str_len = ft_strlen(s);
	if (start >= str_len)
		new = ft_malloc(1);
	else
	{
		if (len > str_len)
			len = str_len;
		new = ft_malloc((len + 1) * sizeof(char));
		while (i < len)
			new[i++] = s[start++];
	}
	new[i] = '\0';
	return (new);
}
