/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhambard <vhambard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 19:09:24 by vhambard          #+#    #+#             */
/*   Updated: 2025/06/26 21:10:05 by vhambard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

void	signal_handler(int sig, siginfo_t *info, void *context)
{
	static int				bit;
	static unsigned char	charachter;

	(void)context;
	if (sig == SIGUSR1)
		charachter |= (1 << bit);
	bit++;
	if (bit == 8)
	{
		if (charachter == '\0')
			ft_putchar('\n');
		else
			ft_putchar(charachter);
		bit = 0;
		charachter = 0;
	}
	if (kill(info->si_pid, SIGUSR1) == -1)
		write(2, "ERROR: Faild to send  acknowledgment\n", 38);
}

void	server_init(void)
{
	struct sigaction	sa;

	sa.sa_sigaction = &signal_handler;
	sigemptyset(&sa.sa_mask);
	sigaddset(&sa.sa_mask, SIGUSR1);
	sigaddset(&sa.sa_mask, SIGUSR2);
	sa.sa_flags = SA_RESTART | SA_SIGINFO;
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
}

int	main(void)
{
	ft_putstr("Server started with PID: ");
	ft_putnbr(getpid());
	ft_putchar('\n');
	ft_putstr("Waiting for messages...\n");
	server_init();
	while (1)
		pause();
	return (0);
}
