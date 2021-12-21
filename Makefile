# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tomartin <tomartin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/04 19:11:19 by tomartin          #+#    #+#              #
#    Updated: 2021/12/21 08:48:09 by tomartin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Collors
BLU = \033[0;34m
GRN = \033[0;32m
YEL = \033[0;33m
RED = \033[0;31m
WHT = \033[0;37m
ORG = \033[38;5;202m

RESET = \033[0m                        
# SO
UNAME := $(shell uname)

# Name of the program
NAME = cub3D

# Compiling flags
FLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address

# Folders
LIBFT_DIR = ./libft/
SRC_DIR = ./src/
INC_DIR = ./includes/
OBJ_DIR = ./obj/
ifeq ($(UNAME), Darwin)
MLX_DIR = ./minilibx/
else
MLX_DIR = ./mlx_linux/
endif
CHECK_DIR= ./src/check/
PAINT_DIR= ./src/paint/

# Source files and object files
SRC_FILES = cube3d.c file_actions.c utils.c load_map.c free_resources.c \
			continue_load_map.c
CHECK_FILES = checker.c errors.c scanmap.c redimension_map.c errors2.c
PAINT_FILES = openwindow.c vector_operation.c key_hook.c ray.c paint_utils.c \
			  moves.c

# Objs
OBJ_FILES = $(SRC_FILES:.c=.o)
OBJ_FILES := $(OBJ_FILES) $(CHECK_FILES:.c=.o)
OBJ_FILES := $(OBJ_FILES) $(PAINT_FILES:.c=.o)

INC_FILES = cube.h check.h paint.h keys.h

# Paths
LIBFT = $(addprefix $(LIBFT_DIR), libft.a)
MLBX = $(addprefix $(LIBFT_DIR), libmlx.a)
OBJ = $(addprefix $(OBJ_DIR), $(OBJ_FILES))
SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))
CHECK = $(addprefix $(CHECK_DIR), $(CHECK_FILES))
PAINT = $(addprefix $(PAINT_DIR), $(PAINT_FILES))

# Libft linkers
ifeq ($(UNAME), Darwin)
LNK  = -L $(LIBFT_DIR) -lft -L $(MLX_DIR) $(MLX_DIR)libmlx.a\
	   -lmlx -framework OpenGL -framework AppKit
else
LNK  = -L $(LIBFT_DIR) -lft -L $(MLX_DIR) $(MLX_DIR)libmlx.a \
	   $(MLX_DIR)libmlx_Linux.a $(MLX_DIR)mlx.h -lXext -lX11
endif

# all rule
all: obj $(LIBFT) $(MLBX) $(NAME) 

obj:
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c 
	@gcc $(FLAGS) -I $(INC_DIR) -I $(LIBFT_DIR) -I $(MLX_DIR) -o $@ -c $<
$(OBJ_DIR)%.o: $(CHECK_DIR)%.c
	@gcc $(FLAGS) -I $(INC_DIR) -I $(LIBFT_DIR) -I $(MLX_DIR) -o $@ -c $<
$(OBJ_DIR)%.o: $(PAINT_DIR)%.c
	@gcc $(FLAGS) -I $(INC_DIR) -I $(LIBFT_DIR) -I $(MLX_DIR) -o $@ -c $<

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(MLBX):
	@make -C $(MLX_DIR)

# Compiling
$(NAME): $(OBJ)
	@echo " ██████╗██╗   ██╗██████╗ ██████╗ ██████╗ "
	@echo "██╔════╝██║   ██║██╔══██╗╚════██╗██╔══██╗"
	@echo "██║     ██║   ██║██████╔╝ █████╔╝██║  ██║"
	@echo "██║     ██║   ██║██╔══██╗ ╚═══██╗██║  ██║"
	@echo "╚██████╗╚██████╔╝██████╔╝██████╔╝██████╔╝"
	@echo " ╚═════╝ ╚═════╝ ╚═════╝ ╚═════╝ ╚═════╝ "
	@gcc $(OBJ) $(FLAGS) $(LNK) -lm -o $(NAME)
	@echo "Compilation OK!!"
	@echo "$(NAME) ready!".

bonus: all

# clean rule
clean:
	@rm -Rf $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean
	@make -C $(MLX_DIR) clean
	@echo "Objects removed!"

# fclean rule
fclean: clean
	@rm -f $(NAME)
	@make -C $(LIBFT_DIR) fclean
	@echo "$(NAME) removed!"

 # re rule
 re: fclean all

 normi:
	@norminette */*.c */*.h

 # phony
 .PHONY: all clean fclean re
