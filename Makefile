# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: irifarac <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/24 10:05:59 by irifarac          #+#    #+#              #
#    Updated: 2024/07/10 10:33:55 by irifarac         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Colours
RED := $(shell tput setaf 1)
GREEN := $(shell tput setaf 2)
RESET := $(shell tput sgr0)

NAME := ft_ls
CFLAGS := -Wall -Wextra -Werror -MMD
CFLAGS += -g

# Folders

OBJDIR = obj
SRCDIR = ./

# Files

SRC = src/main.c \
	  src/ft_utils.c \
	  src/ft_build.c \
	  src/ft_parse.c \
	  src/ft_error.c \
	  src/ft_printf.c \
	  src/ft_getinfo.c \
	  src/ft_print_data.c

OBJ = $(SRC:%.c=$(OBJDIR)/%.o)
DEP = $(patsubst %.c, %.d, $(SRC))
INC = ./inc/ft_ls.h ./ft_printf/includes/ft_printf.h
INC += ./ft_printf/libft/src/libft.h

all: makelibs $(NAME)

makelibs:
	@$(MAKE) -C ft_printf

-include $(DEP)
$(NAME): $(OBJ) $(INC)
	@echo "$(GREEN)Creando ejecutable $@ $(RESET)"
	gcc $(CFLAGS) $(OBJ) -o $@
	@echo "$(GREEN)Compilado $@ $(RESET)"

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(INC)
	@echo "$(GREEN)Compilando objeto $< $(RESET)"
	@mkdir -p $(@D)
	gcc $(CFLAGS) -o $@ -c $<

# Bonus target
bonus: CFLAGS += -DBONUS
bonus: $(NAME)

clean:
	rm -rf ./obj
	@make clean -C ft_printf

fclean: clean
	rm -rf $(NAME)
	@make fclean -C ft_printf

re: fclean all

.PHONY: all clean fclean re
