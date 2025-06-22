/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhambard <vhambard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 19:09:16 by vhambard          #+#    #+#             */
/*   Updated: 2025/06/22 19:15:27 by vhambard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

void	print_message(void)
{
	ft_putstr("Message received: ");
	if (g_server.message)
		ft_putstr(g_server.message);
	ft_putchar('\n');
}