/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vhambard <vhambard@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/22 19:09:01 by vhambard          #+#    #+#             */
/*   Updated: 2025/06/26 21:43:21 by vhambard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include <signal.h>
# include <stdlib.h>
# include <sys/types.h>
# include <unistd.h>

void	server_init(void);
void	signal_handler(int sig, siginfo_t *info, void *context);
void	client_signal_handler(int sig);
void	send_message(pid_t server_pid, const char *message);
void	send_char(pid_t server_pid, char c);
int		ft_atoi(const char *str);
void	ft_putchar(char c);
void	ft_putnbr(int n);
void	ft_putstr(const char *str);


#endif