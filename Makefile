# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lchan <lchan@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/29 03:43:40 by dtanigaw          #+#    #+#              #
#    Updated: 2022/08/30 16:15:17 by lchan            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#	E X E C U T A B L E  N A M E

NAME				=	cub3d

#	CC flags
CC	 				=	clang
#CFLAGS				=	$(MEM)
MEM					=	-g3
#OPT				=	-O2
INC					=	-I inc/


#
#	F I L E S
#

#	Source files

#parsing_check_map.c
SRC_DIR				=	src/
SRC_FILES			=	draw.c \
						exit.c \
						init.c \
						keyhooks.c \
						main.c \
						get_next_line.c \
						get_next_line_utils.c \
						parsing_main.c \
						parsing_check_file.c \
						camera_movement.c \
						player_movement.c \
						raycasting.c \
						system_calls.c
SRC					=	$(addprefix $(SRC_DIR), $(SRC_FILES))

#	OBJ. files
OBJ_DIR				=	obj/
OBJ_FILES			=	$(SRC_FILES:.c=.o)
OBJ					=	$(addprefix $(OBJ_DIR), $(OBJ_FILES))

#	INC. files
INC_DIR				=	inc/
INC_FILES			=	cub3d.h
HEADERS				=	$(addprefix $(INC_DIR), $(INC_FILES))

MLX_MAKE			=	make -s -C
MLX_DIR				=	mlx_linux/
MLX_LIB				=	$(MLX_DIR)libmlx.a
MLX_FLAGS			=	-lX11 -lXext -lm
MLX_HEADER			=	$(MLX_DIR)mlx.h
MLX_INC				=	-I $(MLX_DIR)


#
#	R U L E S
#

#	Colors
GREEN	= \033[32m
YELLOW	= \033[33m
BLUE	= \033[34m
RESET	= \033[0m

#	Build rules
all: $(NAME)

$(MLX_LIB):
	@echo "-> $(YELLOW)Now compiling minilibx...$(RESET)"
	@$(MLX_MAKE) $(MLX_DIR) > /dev/null 2>&1
	@echo -e '-> $(GREEN)OK$(RESET)\n'
	@echo -e '$(YELLOW)-> Now linking $(NAME)...$(RESET)'

$(NAME): $(MLX_LIB) $(OBJ)
	@echo -e '\n$(YELLOW)-> Now compiling $(NAME)...$(RESET)'
	$(CC) $(MLX_FLAGS) -o $@ $(OBJ) $(MLX_LIB)
	@echo -e '-> $(GREEN)$@ successfully compiled !$(RESET)'

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(HEADERS) $(MLX_HEADER)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INC) $(MLX_INC) -o $@ -c $<

#	Clean & other rules
clean:
	make -s clean -C $(MLX_DIR)
	@echo -e '$(BLUE)-> Cleaned minilibx$(RESET)'
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(MLX_LIB) $(NAME)

re: fclean all

.PHONY: all clean fclean re
