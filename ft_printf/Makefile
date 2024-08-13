# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: irifarac <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/07 09:34:40 by irifarac          #+#    #+#              #
#    Updated: 2024/08/12 21:04:05 by israel           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Colors

RED := $(shell tput -Txterm setaf 1)
GREEN := $(shell tput -Txterm setaf 2)
BLUE := $(shell tput -Txterm setaf 4)
RESET := $(shell tput -Txterm sgr0)

NAME := libftprintf.a
LIBFT := libft
CFLAGS := -Wall -Wextra -Werror -MMD
AR := ar rcs

SRC := src/ft_printf.c \
	src/ft_printf_utils.c \
	src/ft_printf_string.c \
	src/ft_printf_number.c \
	src/ft_printf_longlong.c \
	src/ft_printf_ptr.c

OBJ := $(SRC:.c=.o)
DEP := $(patsubst %.c,%.d,$(SRC))
LIBFT := libft

all: makelibs $(NAME)

makelibs:
	@make -C $(LIBFT)

-include $(DEP)
$(NAME): $(OBJ) includes/ft_printf.h libft/libft.a
	@make -C $(LIBFT)
	@cp libft/libft.a .
	@mv libft.a $(NAME)
	@$(AR) $(NAME) $(OBJ)
	@echo "$(BLUE)ft_printf compiled$(RESET)"

%.o: %.c includes/ft_printf.h libft/src/libft.h
	@echo "$(BLUE)Compiling... $<$(RESET)"
	gcc $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	rm -f $(OBJ)
	rm -f $(DEP)
	@make clean -C $(LIBFT)
	@echo "$(RED)ft_printf objets cleaned$(RESET)"

fclean: clean
	@make fclean -C $(LIBFT)
	rm -f $(NAME)
	rm -f $(LIBFT)/libft.a
	@echo "$(RED)executable files cleaned$(RESET)"

re: fclean all

.PHONY: all clean fclean re

