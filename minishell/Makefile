NAME        =   minishell
LIBFT_DIR	=	libft
LIB_SOURCES	=	$(wildcard $(LIBFT_DIR)/*.c)
LIBFT_OBJ	=	$(patsubst %.c, %.o, $(LIB_SOURCES))
SRC_DIR     =   src
OBJ_DIR     =   obj
INCS        =   -Iinclude
HEADERS     =   $(wildcard ./include/*.h)
SOURCES     =   $(wildcard $(SRC_DIR)/*.c) $(wildcard $(LIBFT_DIR)/*.c)
OBJS        =   $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o , $(SOURCES))
CC          =   cc
CFLAGS		=	-Wall -Wextra -Werror
READ      	=   -lreadline
RM          =   rm -rf
MK          =   mkdir -p
.DEFAULT_GOAL= all

all:    $(LIBFT_OBJ) $(OBJ_DIR) $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(READ) $(INCS) -o $(NAME) $(OBJS)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	$(CC) $(CFLAGS) $(INCS) -c $< -o $@ 

$(OBJ_DIR): $(SRC_DIR)
	$(MK) $(OBJ_DIR)


%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJ_DIR)
	$(RM) $(LIBFT_OBJ)

fclean:	clean
	$(RM) $(NAME)

re:			fclean all 
.PHONY:		all clean fclean re 