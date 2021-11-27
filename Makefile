# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tomartin <tomartin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/04 19:11:19 by tomartin          #+#    #+#              #
#    Updated: 2021/11/27 16:05:20 by tomartin         ###   ########.fr        #
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

# Name of the program
NAME = cube3d

# Compiling flags
FLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address

# Folders
LIBFT_DIR = ./libft/
SRC_DIR = ./src/
INC_DIR = ./includes/
OBJ_DIR = ./obj/
MLX_DIR = ./minilibx/

# Source files and object files
SRC_FILES = cube3d.c file_actions.c

# Objs
OBJ_FILES = $(SRC_FILES:.c=.o)

# Paths
LIBFT = $(addprefix $(LIBFT_DIR), libft.a)
MLBX = $(addprefix $(LIBFT_DIR), libmlx.a)
OBJ = $(addprefix $(OBJ_DIR), $(OBJ_FILES))
SRC = $(addprefix $(SRC_DIR), $(SRC_FILES))

# Libft linkers
LNK  = -L $(LIBFT_DIR) -lft -L $(MLX_DIR) \
	   -lmlx -framework OpenGL -framework AppKit

# all rule
all: obj $(LIBFT) $(MLBX) $(NAME) 

obj:
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c 
	@gcc $(FLAGS) -I $(INC_DIR) -I $(LIBFT_DIR) -o $@ -c $<
#$(OBJ_DIR)%.o: $(ERRORS_DIR)%.c 
#	@gcc $(FLAGS) $(F_RL) -I $(INC_DIR) -I $(LIBFT_DIR) -o $@ -c $<

$(LIBFT):
	@make -C $(LIBFT_DIR)

$(MLBX):
	@make -C $(MLX_DIR)

# Compiling
$(NAME): $(OBJ)
	@echo " ██████╗██╗   ██╗██████╗ ███████╗██████╗ ██████╗ "
	@echo "██╔════╝██║   ██║██╔══██╗██╔════╝╚════██╗██╔══██╗"
	@echo "██║     ██║   ██║██████╔╝█████╗   █████╔╝██║  ██║"
	@echo "██║     ██║   ██║██╔══██╗██╔══╝   ╚═══██╗██║  ██║"
	@echo "╚██████╗╚██████╔╝██████╔╝███████╗██████╔╝██████╔╝"
	@echo " ╚═════╝ ╚═════╝ ╚═════╝ ╚══════╝╚═════╝ ╚═════╝ "
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
