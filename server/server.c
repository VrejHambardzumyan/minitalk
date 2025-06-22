/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhambard <vhambard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 19:09:24 by vhambard          #+#    #+#             */
/*   Updated: 2025/06/22 20:53:03 by vhambard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

/* 
 * Global variable justified: Signal handlers cannot receive additional 
 parameters,
 so we need global state to maintain message reconstruction across 
 signal calls.
 This structure contains all necessary data for bit-by-bit message assembly.
 */
t_server_data	g_server = {0, 0, NULL, 0, 0};

int	main(void)
{
	ft_putstr("Server started with PID: ");
	ft_putnbr(getpid());
	ft_putchar('\n');
	ft_putstr("Waiting for messages...\n");
	server_init();
	/* Keep server running */
	while (1)
		pause();
	return (SUCCESS);
}

void	server_init(void)
{
	struct sigaction	sa;
	/* Initialize sigaction structure */
	sa.sa_sigaction = signal_handler;
	sa.sa_flags = SA_SIGINFO;
	sigemptyset(&sa.sa_mask);
	/* Set up signal handlers */
	if (sigaction(SIGUSR1, &sa, NULL) == ERROR)
		error_exit("Error: Failed to set SIGUSR1 handler");
	if (sigaction(SIGUSR2, &sa, NULL) == ERROR)
		error_exit("Error: Failed to set SIGUSR2 handler");
}

void	signal_handler(int sig, siginfo_t *info, void *context)
{
	int	bit;

	(void)context;
	(void)info;
	/* Determine bit value based on signal */
	if (sig == SIGUSR1)
		bit = 1;
	else if (sig == SIGUSR2)
		bit = 0;
	else
		return ;

	process_bit(bit);
}

void	process_bit(int bit)
{	/* Shift current character left and add new bit */
	g_server.current_char = (g_server.current_char << 1) | bit;
	g_server.bit_count++;
	/* If we have received 8 bits, we have a complete character */
	if (g_server.bit_count == 8)
	{	/* Check if we need to expand message buffer */
		if (g_server.message_len >= g_server.message_capacity - 1)
		{
			g_server.message_capacity = (g_server.message_capacity == 0) ? 64 : g_server.message_capacity * 2;
			g_server.message = realloc(g_server.message, g_server.message_capacity);
			if (!g_server.message)
				error_exit("Error: Memory allocation failed");
		}
		/* Add character to message */
		g_server.message[g_server.message_len] = g_server.current_char;
		g_server.message_len++;
		/* If character is null terminator, print message and reset */
		if (g_server.current_char == '\0')
		{
			print_message();
			/* Reset for next message */
			free(g_server.message);
			g_server.message = NULL;
			g_server.message_len = 0;
			g_server.message_capacity = 0;
		}
		/* Reset character and bit count */
		g_server.current_char = 0;
		g_server.bit_count = 0;
	}
}
