# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: irifarac <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/24 10:05:59 by irifarac          #+#    #+#              #
#    Updated: 2024/08/15 21:54:49 by israel           ###   ########.fr        #
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

# Libraries
LIBFT_DIR := ft_printf/libft
LIBFT := $(LIBFT_DIR)/libft.a
FT_PRINTF_DIR := ft_printf
FT_PRINTF := $(FT_PRINTF_DIR)/libftprintf.a

# Files

SRC = src/main.c \
	  src/ft_utils.c \
	  src/ft_build.c \
	  src/ft_parse.c \
	  src/ft_error.c \
	  src/ft_getinfo.c \
	  src/ft_sort.c \
	  src/ft_sort_dir.c \
	  src/ft_parse_flags.c \
	  src/ft_print_colors.c \
	  src/ft_print_file.c \
	  src/ft_iter.c \
	  src/ft_print_data.c

OBJ = $(SRC:%.c=$(OBJDIR)/%.o)
DEP = $(patsubst %.c, %.d, $(SRC))
INC = ./inc/ft_ls.h
INC_PRINTF = ./ft_printf/includes/ft_printf.h
INC_LIBFT = ./ft_printf/libft/src/libft.h
INC_DIRS = -I./inc -I./ft_printf/includes -I./ft_printf/libft/src

all: $(NAME)

$(NAME): $(OBJ) $(FT_PRINTF)
	@echo "$(GREEN)Creando ejecutable $@ $(RESET)"
	gcc $(CFLAGS) $(OBJ) -L$(FT_PRINTF_DIR) -lftprintf -o $@
	@echo "$(GREEN)Compilado $@ $(RESET)"

$(FT_PRINTF): $(FT_PRINTF_DIR)/src/*.c $(LIBFT) $(INC_PRINTF)
	@$(MAKE) -C $(FT_PRINTF_DIR)

$(LIBFT): $(LIBFT_DIR)/src/*.c $(INC_LIBFT)
	@$(MAKE) -C $(LIBFT_DIR)


-include $(DEP)

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(INC)
	@echo "$(GREEN)Compilando objeto $< $(RESET)"
	@mkdir -p $(@D)
	gcc $(CFLAGS) $(INC_DIRS) -o $@ -c $<

# Bonus target
bonus: CFLAGS += -DBONUS
bonus: re

clean:
	rm -rf ./obj
	@make clean -C $(FT_PRINTF_DIR)
	@make clean -C $(LIBFT_DIR)

fclean: clean
	rm -rf $(NAME)
	@make fclean -C $(FT_PRINTF_DIR)
	@make fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re
