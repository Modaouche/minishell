# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: modaouch <modaouch@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/06/20 17:03:40 by modaouch          #+#    #+#              #
#    Updated: 2019/02/01 07:58:30 by modaouch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC =	srcs/main.c\
	srcs/list.c\
	srcs/list2.c\
	srcs/exec_cmd.c\
	srcs/error_msg.c\
	srcs/ft_utility.c\
	srcs/ft_utility2.c\
	srcs/exec_shell.c\
	srcs/signal_handler.c\
	srcs/parsing/parse_stdin.c\
	srcs/parsing/parse_stdin2.c\
	srcs/builtins/builtin_env.c\
	srcs/builtins/builtin_exit.c\
	srcs/builtins/builtin_setenv.c\
	srcs/builtins/builtin_pwd.c\
	srcs/builtins/builtin_unsetenv.c\
	srcs/builtins/builtin_echo.c\
	srcs/builtins/builtin_cd.c\
	srcs/builtins/builtin_cd2.c\
	srcs/builtins/builtin_cd3.c

LIB = libft/libft.a\
      libft/ft_printf/libftprintf.a\

OBJ = $(SRC:.c=.o)
#OBJ = $(patsubst %.c,%.o, $(SRC))

INCLUDES = libft/ft_printf/includes/ft_conv.h\
		   libft/ft_printf/includes/ft_printf.h\
		   libft/libft.h\
		   includes/minishell.h

LIBFT = libft

LIBFTPRINTF = libft/ft_printf/

DIRPRINTF = libft/ft_printf/src\
	    libft/ft_printf/includes\
	    libft/ft_printf/src/libft

DEPEN = $(SRC) $(OBJ) $(INCLUDES) Makefile libft/ft_printf/Makefile\
		$(LIBFT) $(LIBFTPRINTF)

CC = gcc

CFLAGS = -Wall -Wextra -Werror\
#		  -g -fsanitize=address\
		  -fno-omit-frame-pointer\
		  -fsanitize-address-use-after-scope

all: $(NAME)


$(NAME): $(DEPEN)
	make -C $(LIBFT) all
	make -C $(LIBFTPRINTF) all
	$(CC) $(CFLAGS) $(OBJ) $(LIB) -o $(NAME)

clean:
	make clean -C $(LIBFT)
	make clean -C $(LIBFTPRINTF)
	rm -f $(OBJ)

fclean:
	make fclean -C $(LIBFT)
	make fclean -C $(LIBFTPRINTF)
	/bin/rm -f $(OBJ)
	/bin/rm -f ./$(NAME)

re: fclean all
