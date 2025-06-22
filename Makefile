# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vhambard <vhambard@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/22 17:31:39 by vhambard          #+#    #+#              #
#    Updated: 2025/06/22 20:17:46 by vhambard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Program names
SERVER = minitalk_server
CLIENT = minitalk_client

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = -I./include

# Directories
SRC_DIR = .
SERVER_DIR = server
CLIENT_DIR = client
INCLUDE_DIR = include

# Source files
SERVER_SRCS = $(SERVER_DIR)/server.c $(SERVER_DIR)/server_utils.c
CLIENT_SRCS = $(CLIENT_DIR)/client.c
UTILS_SRCS = utils.c

# Object files
SERVER_OBJS = $(SERVER_SRCS:.c=.o)
CLIENT_OBJS = $(CLIENT_SRCS:.c=.o)
UTILS_OBJS = $(UTILS_SRCS:.c=.o)

# Colors for pretty output
GREEN = \033[0;32m
RED = \033[0;31m
RESET = \033[0m

# Default target
all: $(SERVER) $(CLIENT)

# Server compilation
$(SERVER): $(SERVER_OBJS) $(UTILS_OBJS)
	@echo "$(GREEN)Linking server...$(RESET)"
	$(CC) $(CFLAGS) $(SERVER_OBJS) $(UTILS_OBJS) -o $(SERVER)
	@echo "$(GREEN)Server compiled successfully!$(RESET)"

# Client compilation
$(CLIENT): $(CLIENT_OBJS) $(UTILS_OBJS)
	@echo "$(GREEN)Linking client...$(RESET)"
	$(CC) $(CFLAGS) $(CLIENT_OBJS) $(UTILS_OBJS) -o $(CLIENT)
	@echo "$(GREEN)Client compiled successfully!$(RESET)"

# Object file compilation
%.o: %.c
	@echo "$(GREEN)Compiling $<...$(RESET)"
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Clean object files
clean:
	@echo "$(RED)Cleaning object files...$(RESET)"
	rm -f $(SERVER_OBJS) $(CLIENT_OBJS) $(UTILS_OBJS)

# Clean everything
fclean: clean
	@echo "$(RED)Cleaning executables...$(RESET)"
	rm -f $(SERVER) $(CLIENT)

# Rebuild everything
re: fclean all

# Test the programs
test: all
	@echo "$(GREEN)Starting server in background...$(RESET)"
	./$(SERVER) &
	@sleep 1
	@echo "$(GREEN)Sending test message...$(RESET)"
	./$(CLIENT) `pgrep minitalk_server` "Hello, 42!"
	@sleep 1
	@pkill minitalk_server

# Phony targets
.PHONY: all clean fclean re test