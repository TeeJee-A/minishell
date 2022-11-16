/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataji <ataji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 15:05:33 by ataji             #+#    #+#             */
/*   Updated: 2022/11/15 22:45:59 by ataji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	my_number(long int n)
{
	int	c;

	c = 0;
	if (n < 0)
	{
		n = n * -1;
		c++;
	}
	if (n == 0)
		c++;
	while (n != 0)
	{
		c++;
		n = n / 10;
	}
	return (c);
}

char	*my_itoa(int n)
{
	char		*str;
	long int	k;
	int			size;
	int			d;

	k = n;
	size = my_number(n);
	str = (char *)malloc((size + 1) * sizeof(char));
	if (!str)
		return (NULL);
	str[size--] = '\0';
	if (k < 0)
	{
		k *= -1;
		d = 1;
		str[0] = '-';
	}
	else
		d = 0;
	while (size >= d)
	{
		str[size--] = k % 10 + '0';
		k = k / 10;
	}
	return (str);
}
