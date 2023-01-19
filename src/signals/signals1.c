/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals1.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfaouzi <kfaouzi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 20:18:59 by kfaouzi           #+#    #+#             */
/*   Updated: 2022/11/22 10:25:53 by kfaouzi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/utils_char_str.h"

void	stay_in_shell(int _signal)
{
	if (g_data.is_running)
		return ;
	if (SIGINT == _signal)
	{
		g_data.exit_status = 1;
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	handel_sig_hr(int _signal)
{
	(void)_signal;
	g_data.exec = -1;
	rl_done = 1;
}
