# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: irifarac <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/07 09:34:40 by irifarac          #+#    #+#              #
#    Updated: 2024/05/13 20:45:02 by israel           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := libftprintf.a
LIBFT := libft
CFLAGS := -Wall -Wextra -Werror -MMD
AR := ar rcs

SRC := src/ft_printf.c \
	src/ft_printf_utils.c \
	src/ft_printf_string.c \
	src/ft_printf_number.c \
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
	@echo "ft_printf compiled"

%.o: %.c includes/ft_printf.h libft/src/libft.h
	@echo "Compiling"
	gcc $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
	rm -f $(OBJ)
	rm -f $(DEP)
	@make clean -C $(LIBFT)
	@echo "ft_printf objets cleaned"

fclean: clean
	@make fclean -C $(LIBFT)
	rm -f $(NAME)
	rm -f $(LIBFT)/libft.a
	@echo "executable files cleaned"

re: fclean all

.PHONY: all clean fclean re

