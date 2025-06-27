/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhambard <vhambard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 17:35:14 by vhambard          #+#    #+#             */
/*   Updated: 2025/06/26 21:38:59 by vhambard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

int	g_global_received = 0;

int	validate(char *PID)
{
	int	i;
	int	pid;

	i = 0;
	while (PID[i])
	{
		if (PID[i] < '0' || PID[i] > '9')
			return (0);
		i++;
	}
	pid = ft_atoi(PID);
	return (pid);
}

void	client_signal_handler(int sig)
{
	if (sig == SIGUSR1)
		g_global_received = 1;
}

void	send_message(pid_t server_pid, const char *message)
{
	int	i;

	if (!message)
		return ;
	i = 0;
	while (message[i])
	{
		send_char(server_pid, message[i]);
		i++;
	}
	send_char(server_pid, '\0');
}

void	send_char(pid_t server_pid, char c)
{
	int	bit_position;
	int	signal_sent;

	bit_position = 0;
	while (bit_position < 8)
	{
		g_global_received = 0;
		if ((c & (1 << bit_position)) != 0)
			signal_sent = kill(server_pid, SIGUSR1);
		else
			signal_sent = kill(server_pid, SIGUSR2);
		if (signal_sent == -1)
		{
			write(2, "ERROR: Faild to send signal\n", 29);
			exit(1);
		}
		while (g_global_received == 0)
			usleep(100);
		bit_position++;
	}
}

int	main(int argc, char **argv)
{
	pid_t	server_pid;

	if (argc != 3)
	{
		ft_putstr("Usage: ./client <server_pid> <message>\n");
		ft_putstr("Example: ./client 12345 \"Hello, World!\"\n");
		return (1);
	}
	signal(SIGUSR1, client_signal_handler);
	server_pid = validate(argv[1]);
	if (server_pid == 0)
	{
		write(2, "Error: Invalid server PID\n", 27);
		return (1);
	}
	send_message(server_pid, argv[2]);
	ft_putstr("Message sent successfully!\n");
	return (0);
}
