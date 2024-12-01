# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tomoron <tomoron@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/07/17 15:48:36 by tomoron           #+#    #+#              #
#    Updated: 2024/10/29 20:43:12 by tomoron          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC          := clang
CFLAGS      := -g -Wextra -Werror -Wall


LIBFT_DIR   := ./libft
LFT		 	:= $(LIBFT_DIR)/libft.a
LIBFT       := -L$(LIBFT_DIR) -lft

DAY         := $(DAY)

INCLUDES	:= -I./includes -I./$(LIBFT_DIR)/includes

SRCS_DIR    := srcs/day$(DAY)
OBJS_DIR    := $(SRCS_DIR)/.objs

MAIN_SRC	:= srcs/main.c
MAIN_OBJ	:= srcs/.objs/main.o

SRCS        := $(wildcard $(SRCS_DIR)/*.c)
OBJS        := $(patsubst $(SRCS_DIR)/%.c, $(OBJS_DIR)/%.o, $(SRCS)) $(MAIN_OBJ)

NAME        := program_day$(DAY)

BLACK       := \033[30;49;3m
RED         := \033[31;49;3m
GREEN       := \033[32;49;3m
YELLOW      := \033[33;49;3m
BLUE        := \033[34;49;3m
MAGENTA     := \033[35;49;3m
CYAN        := \033[36;49;3m
WHITE       := \033[37;49;3m

BBLACK		=	\033[30;49;3;1m
BRED		=	\033[31;49;3;1m
BGREEN		=	\033[32;49;3;1m
BYELLOW		=	\033[33;49;3;1m
BBLUE		=	\033[34;49;3;1m
BMAGENTA	=	\033[35;49;3;1m
BCYAN		=	\033[36;49;3;1m
BWHITE		=	\033[37;49;3;1m

RESET       := \033[0m
LINE_CLR    := \33[2K\r

all: $(NAME)

$(NAME): $(LFT) $(OBJS)
	@printf " $(LINE_CLR)$(WHITE) Linking objects into $(NAME)...$(RESET)\n"
	@$(CC) $(CFLAGS) $(INCLUDES) $(OBJS) $(LIBFT) -o $(NAME)
	@printf "\n $(LINE_CLR)$(BWHITE)$(NAME) successfully created!$(RESET)\n\n"

$(LFT):
	@make -j -C $(LIBFT_DIR)

$(MAIN_OBJ): $(MAIN_SRC)
	@printf "\n $(LINE_CLR)$(BWHITE) Compiling $(BGREEN)$<...$(RESET)\n"
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c | $(OBJS_DIR)
	@printf "\n $(LINE_CLR)$(BWHITE) Compiling $(BGREEN)$<...$(RESET)\n"
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)
	@mkdir -p srcs/.objs

clean:
	@find srcs/ -name "*.o" -delete
	@find srcs/ -type d -name ".objs" -exec rm -rf {} +
	@rm -f $(OBJS)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	@rm -f program*
	@rm -f $(NAME)
	@printf " $(BWHITE)$(NAME):$(BRED) cleaned.$(RESET)\n"
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
.SILENT: