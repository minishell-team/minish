CC 				= gcc -g
RM				= rm -rf
CFLAGS 			= -Wall -Wextra -Werror
NAME 			= minishell

#READLINE_LIB 	= -lreadline -L/usr/local/opt/readline/lib
#READLINE_INC	= -I/usr/local/opt/readline/include

READLINE_LIB 	= -lreadline -L/opt/homebrew/opt/readline/lib
READLINE_INC	= -I/opt/homebrew/opt/readline/include

LIBFT		= libft.a
LIBFT_DIR	= libft

SRC_DIR 	= srcs
SRC 		= srcs/main.c srcs/begin_util.c \
	  	  	  srcs/parse.c srcs/exec.c \
			  srcs/parse_cmd.c srcs/parse_env_cnt.c\
			  srcs/parse_env.c srcs/parse_utils.c

OBJ_DIR 	= objs
OBJ 		= $(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all : 		$(NAME)

$(NAME) : 	$(LIBFT) $(OBJ)
			$(CC) $(CFLAGS) -o $@ $(OBJ) $(READLINE_LIB) $(READLINE_INC) \
			$(LIBFT)

$(LIBFT) :
			cd $(LIBFT_DIR); make
			cp $(LIBFT_DIR)/$(LIBFT) ./

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
			mkdir -p $(OBJ_DIR)
			$(CC) $(CFLAGS) -c $< -o $(<:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o) \
			$(READLINE_INC)

clean :
			cd $(LIBFT_DIR); make clean
			$(RM) $(OBJ) $(OBJ_DIR)

fclean : 	clean
			cd $(LIBFT_DIR); make fclean
			$(RM) $(NAME) $(LIBFT)

re : 		fclean all

.PHONY :	all clean fclean
