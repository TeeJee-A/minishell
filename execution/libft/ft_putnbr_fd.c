/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataji <ataji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 18:59:51 by ataji             #+#    #+#             */
/*   Updated: 2022/11/15 22:46:58 by ataji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils_char_str.h"

void	my_putnbr_fd(int n, int fd)
{
	long int	nb;

	nb = n;
	if (nb < 0)
	{
		my_putchar_fd('-', fd);
		nb *= -1;
	}
	if (nb >= 10)
	{
		my_putnbr_fd(nb / 10, fd);
		my_putnbr_fd(nb % 10, fd);
	}
	if (nb >= 0 && nb < 10)
	{
		my_putchar_fd(nb + '0', fd);
	}
}
