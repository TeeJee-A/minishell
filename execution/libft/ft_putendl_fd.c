/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putendl_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ataji <ataji@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 18:42:55 by ataji             #+#    #+#             */
/*   Updated: 2022/11/16 08:37:47 by ataji            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils_char_str.h"

void	my_putendl_fd(char *s, int fd)
{
	if (!s)
		return ;
	my_putstr_fd(s, fd);
	my_putchar_fd('\n', fd);
}
