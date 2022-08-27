

#	E X E C U T A B L E  N A M E 

NAME				=	cub3d

#	CC flags
CC	 				=	clang
#CFLAGS				=
#MEM				=	-g3 -fsanitize=address
#OPT				=	-O2
IFLAG				=	-I inc/


#
#	F I L E S
#

#	Source files
SRC_DIR				=	src/
SRC_FILES			=	draw.c \
						exit.c \
						init.c \
						main.c \
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
INC					=	$(addprefix $(INC_DIR), $(INC_FILES))

MLX_MAKE			=	make -s -C
MLX_DIR				=	mlx_linux/
MLX_LIB				=	$(MLX_DIR)/libmlx.a
MLX_FLAGS			=	-lX11 -lXext -lm
MLX_INC				=	-I$(MLX_DIR)


#
#	R U L E S
#

#	Colors
GREEN	= \033[32m
BLUE	= \033[34m
RESET	= \033[0m

#	Build rules
all: $(NAME)

$(NAME): mlx $(OBJ)
	$(CC) $(MLX_FLAGS) -o $@ $^
	@echo -e '$@ successfully compiled !'

mlx:
	@echo "Now compiling minilibx..."
	@$(MLX_MAKE) $(MLX_DIR) > /dev/null 2>&1
	@echo -e '$(GREEN)OK$(RESET)'

$(OBJ_DIR)%.o: $(SRC_DIR)%.c $(INC)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(IFLAG) $(CFLAGS) -o $@ -c $<

#	Clean & other rules
clean:
	make -s clean -C $(MLX_DIR)
	@echo -e '$(BLUE)-> Cleaned minilibx$(RESET)'
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(MLX_LIB) $(NAME)

re: fclean all

.PHONY: all clean fclean re
