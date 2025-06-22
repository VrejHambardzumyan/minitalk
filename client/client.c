/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhambard <vhambard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 17:35:14 by vhambard          #+#    #+#             */
/*   Updated: 2025/06/22 18:38:46 by vhambard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minitalk.h"

int	main(int argc, char **argv)
{
	pid_t	server_pid;

	if (client_init(argc, argv) == ERROR)
		return (EXIT_FAILURE);

	server_pid = ft_atoi(argv[1]);
	if (server_pid <= 0)
		error_exit("Error: Invalid server PID");

	ft_putstr("Sending message to server PID ");
	ft_putnbr(server_pid);
	ft_putstr(": \"");
	ft_putstr(argv[2]);
	ft_putstr("\"\n");

	send_message(server_pid, argv[2]);

	ft_putstr("Message sent successfully!\n");
	return (SUCCESS);
}

int	client_init(int argc, char **argv)
{
	if (argc != 3)
	{
		ft_putstr("Usage: ");
		ft_putstr(argv[0]);
		ft_putstr(" <server_pid> <message>\n");
		ft_putstr("Example: ");
		ft_putstr(argv[0]);
		ft_putstr(" 12345 \"Hello, World!\"\n");
		return (ERROR);
	}
	return (SUCCESS);
}

void	send_message(pid_t server_pid, const char *message)
{
	int	i;

	if (!message)
		return ;

	i = 0;
	/* Send each character of the message */
	while (message[i])
	{
		send_char(server_pid, message[i]);
		i++;
	}
	/* Send null terminator to indicate end of message */
	send_char(server_pid, '\0');
}

void	send_char(pid_t server_pid, char c)
{
	int	bit_position;

	bit_position = 7;
	/* Send each bit of the character, starting from the most significant bit */
	while (bit_position >= 0)
	{
		send_bit(server_pid, (c >> bit_position) & 1);
		bit_position--;
	}
}

void	send_bit(pid_t server_pid, int bit)
{
	if (bit == 1)
	{
		if (kill(server_pid, SIGUSR1) == ERROR)
			error_exit("Error: Failed to send SIGUSR1 signal");
	}
	else
	{
		if (kill(server_pid, SIGUSR2) == ERROR)
			error_exit("Error: Failed to send SIGUSR2 signal");
	}
	/* Small delay to prevent overwhelming the server */
	usleep(SIGNAL_DELAY);
}