NAME        	=   minishell
INCS        	=   -Iinclude
HEADERS     	=   $(wildcard ./include/*.h) Makefile
CC          	=   cc
CFLAGS			=	-Wall -Wextra -Werror
READ      		=   -lreadline
RM          	=   rm -rf
MK          	=   mkdir -p

#GRAY COLOR	
GRAY        	=   \033[38;5;8m
GREEN			=	\033[38;5;46m
RED				=	\033[38;5;196m
RESET       	=   \033[0m

#LIBFT	
LIBFT_DIR		=	libft
LIBFT_SRCS		=	$(wildcard $(LIBFT_DIR)/*.c)
LIBFT_OBJ		=	$(patsubst $(LIBFT_DIR)/%.c, $(OBJ_DIR)/%.o, $(LIBFT_SRCS))
#MANDATORY	
SRC_DIR     	=   src
OBJ_DIR     	=   obj
SRCS     		=   $(wildcard $(SRC_DIR)/*.c)
OBJS        	=   $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o , $(SRCS))

.DEFAULT_GOAL	=	all

all:    $(OBJ_DIR) $(NAME)

$(NAME): $(OBJS) $(LIBFT_OBJ)
	@echo "$(GREEN)Sources and Libft compiled.$(RESET)"
	@$(CC) $(CFLAGS) $(READ) $(INCS) -o $(NAME) $(OBJS) $(LIBFT_OBJ)
	@echo "$(GRAY)$(CC) $(CFLAGS) $(READ) $(INCS) -o $(NAME) $(OBJS) $(LIBFT_OBJ) $(RESET)"
	@echo "$(GREEN)Build completed.$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	@$(CC) $(CFLAGS) $(INCS) -c $< -o $@ $
	@echo "$(GRAY)$(CC) $(CFLAGS) $(INCS) -c $< -o $@ $(RESET)"

$(OBJ_DIR)/%.o: $(LIBFT_DIR)/%.c $(HEADERS)
	@$(CC) $(CFLAGS) $(INCS) -c $< -o $@
	@echo "$(GRAY)$(CC) $(CFLAGS) $(INCS) -c $< -o $@ $(RESET)"

$(OBJ_DIR): $(SRC_DIR) $(LIBFT_DIR)
	@$(MK) $(OBJ_DIR)

%.o: %.c $(HEADERS)
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "$(GRAY)$(CC) $(CFLAGS) -c $< -o $@ $(RESET)"

clean:
	@$(RM) $(OBJ_DIR)
	@echo "$(GRAY)$(RM) $(OBJ_DIR)$(RESET)"
	@echo "$(RED)Cleaned$(RESET)"

fclean:	clean
	@$(RM) $(NAME)
	@echo "$(GRAY)$(RM) $(NAME)$(RESET)"
	@echo "$(RED)Fcleaned$(RESET)"

re:			fclean all 
.PHONY:		all clean fclean re 