/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhambard <vhambard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 19:09:01 by vhambard          #+#    #+#             */
/*   Updated: 2025/06/22 20:50:38 by vhambard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# define _POSIX_C_SOURCE 200809L
# define _DEFAULT_SOURCE

# include <signal.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>

/* ************************************************************************** */
/*                                 MACROS                                     */
/* ************************************************************************** */

# define SUCCESS 0
# define ERROR -1
# define SIGNAL_DELAY 100

/* ************************************************************************** */
/*                            GLOBAL STRUCTURE                               */
/* ************************************************************************** */

typedef struct s_server_data
{
	char	current_char;
	int		bit_count;
	char	*message;
	int		message_len;
	int		message_capacity;
}	t_server_data;

/* Global variable for server (justified: needed for signal handler) */
extern t_server_data	g_server;

/* ************************************************************************** */
/*                             SERVER FUNCTIONS                              */
/* ************************************************************************** */

void	server_init(void);
void	signal_handler(int sig, siginfo_t *info, void *context);
void	process_bit(int bit);
void	print_message(void);

/* ************************************************************************** */
/*                             CLIENT FUNCTIONS                              */
/* ************************************************************************** */

int		client_init(int argc, char **argv);
void	send_message(pid_t server_pid, const char *message);
void	send_char(pid_t server_pid, char c);
void	send_bit(pid_t server_pid, int bit);

/* ************************************************************************** */
/*                             UTILITY FUNCTIONS                             */
/* ************************************************************************** */

int		ft_atoi(const char *str);
void	ft_putstr(const char *str);
void	ft_putchar(char c);
void	ft_putnbr(int n);
void	error_exit(const char *message);

#endif