# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: irifarac <irifarac@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/01/17 13:46:45 by irifarac          #+#    #+#              #
#    Updated: 2024/08/21 09:35:42 by irifarac         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Colors

RED := $(shell tput -Txterm setaf 1)
GREEN := $(shell tput -Txterm setaf 2)
YELLOW := $(shell tput -Txterm setaf 3)
BLUE := $(shell tput -Txterm setaf 4)
RESET := $(shell tput -Txterm sgr0)

CREATION_LIB = ar -crs
CFLAGS = -Wall -Werror -Wextra
NAME = libft.a
# Define directories
SRC_DIR = src
OBJ_DIR = obj

# Define source files
SRC =	$(addprefix $(SRC_DIR)/, \
	ft_atoi.c \
	ft_bzero.c \
	ft_calloc.c \
	ft_isalnum.c \
	ft_isalpha.c \
	ft_isascii.c \
	ft_isdigit.c \
	ft_isprint.c \
	ft_memchr.c \
	ft_memcmp.c \
	ft_memcpy.c \
	ft_memmove.c\
	ft_memset.c \
	ft_strchr.c \
	ft_strdup.c \
	ft_strlcat.c \
	ft_strlcpy.c \
	ft_strncpy.c \
	ft_strcpy.c \
	ft_strcat.c \
	ft_strlen.c \
	ft_strncmp.c \
	ft_strcmp.c \
	ft_strnstr.c \
	ft_strrchr.c \
	ft_tolower.c \
	ft_toupper.c \
	ft_itoa.c \
	ft_strjoin.c \
	ft_substr.c \
	ft_strtrim.c \
	ft_strmapi.c \
	ft_striteri.c \
	ft_putchar_fd.c \
	ft_putstr_fd.c \
	ft_putendl_fd.c \
	ft_putnbr_fd.c \
	ft_split.c)

BONUS_SRC = $(addprefix $(SRC_DIR)/, \
			ft_lstnew.c \
			ft_lstadd_front.c \
			ft_lstsize.c \
			ft_lstlast.c \
			ft_lstadd_back.c \
			ft_lstdelone.c \
			ft_lstclear.c \
			ft_lstiter.c \
			ft_lstmap.c)

BONUS_OBJ = $(addprefix $(OBJ_DIR)/, $(BONUS_SRC:.c=.o))
OBJ = $(addprefix $(OBJ_DIR)/, $(notdir $(SRC:.c=.o)))
INCLUDE = $(SRC_DIR)/libft.h

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@echo "$(YELLOW)Compilando $<$(RESET)"
	gcc $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ) $(INCLUDE)
	$(CREATION_LIB) $(NAME) $(OBJ)
	@echo "$(YELLOW)Compiling $(NAME)$(RESET)"

all: $(NAME)

bonus : $(NAME) $(BONUS_OBJ)
	$(CREATION_LIB) $(NAME) $(BONUS_OBJ)
	@echo "Compilando bonus"

clean:
	rm -f $(OBJ) $(BONUS_OBJ)
	echo "$(RED)Cleaning object files $(NAME)$(RESET)"

fclean: clean
	rm -f $(NAME)
	rm -rf $(OBJ_DIR)
	echo "$(RED)Cleaning $(NAME)$(RESET)"

re: fclean all

.PHONY: all clean fclean re bonus
