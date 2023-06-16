NAME        =   minishell
INCS        =   -Iinclude
HEADERS     =   $(wildcard ./include/*.h)
CC          =   cc
CFLAGS		=	-Wall -Wextra -Werror
READ      	=   -lreadline
RM          =   rm -rf
MK          =   mkdir -p

#LIBFT
LIBFT_DIR	=	libft
LIBFT_OBJ_D	=	obj
LIBFT_SRCS	=	$(wildcard $(LIBFT_DIR)/*.c)
LIBFT_OBJ	=	$(patsubst $(LIBFT_DIR)/%.c, $(LIBFT_OBJ_D)/%.o, $(LIBFT_SRCS))
#MANDATORY
SRC_DIR     =   src
OBJ_DIR     =   obj
SRCS     	=   $(wildcard $(SRC_DIR)/*.c)
OBJS        =   $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o , $(SRCS))

.DEFAULT_GOAL= all

all:    $(LIBFT_OBJ_D) $(OBJ_DIR) $(NAME)

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