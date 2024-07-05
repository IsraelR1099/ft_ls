# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: irifarac <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/24 10:05:59 by irifarac          #+#    #+#              #
#    Updated: 2024/07/05 11:46:09 by irifarac         ###   ########.fr        #
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
	  src/ft_getinfo.c

OBJ = $(SRC:%.c=$(OBJDIR)/%.o)
DEP = $(patsubst %.c, %.d, $(SRC))
INC = ./inc/ft_ls.h

all: $(NAME)


-include $(DEP)
$(NAME): $(OBJ) $(INC)
	@echo "$(GREEN)Creando ejecutable $@ $(RESET)"
	gcc $(CFLAGS) $(OBJ) -o $@
	@echo "$(GREEN)Compilado $@ $(RESET)"

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(INC)
	@echo "$(GREEN)Compilando objeto $< $(RESET)"
	@mkdir -p $(@D)
	gcc $(CFLAGS) -o $@ -c $<

clean:
	rm -rf ./obj

fclean: clean
	rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re
