# MAIN
NAME			=	minishell
CC				=	cc
RM          	=   rm -rf
MK          	=   mkdir -p
CFLAGS			=	-Wall -Wextra -Werror

# COLORS
GRAY			=	\033[38;5;8m
GREEN			=	\033[38;5;46m
RED				=	\033[38;5;196m
RESET			=	\033m[0m

# LIBRARIES
LIBFT_DIR		=	./libs/libft
LIBFT			=	$(LIBFT_DIR)/libft.a
PRINTF_DIR		=	./libs/ft_dprintf
PRINTF			=	$(PRINTF_DIR)/ft_dprintf.a
GNL_DIR			=	./libs/get_next_line
GNL				=	$(GNL_DIR)/get_next_line.a
INCS_DIR		=	./include

# DEPENDENCIES
DEPS			=	$(wildcard $(INCS_DIR)/*.h) Makefile

# SOURCES
SRC_DIR			=	./src
BUILD			=	./build
SUBDIRS			=	lexer parser executer parser utils
SRCS			+=	$(foreach dir, $(SUBDIRS), \
					$(wildcard $(SRC_DIR)/$(dir)/*.c))

# OBJECTS
OBJS			+=	$(foreach dir, $(SUBDIRS), \
					$(patsubst $(SRC_DIR)/$(dir)/%.c, $(BUILD)/%.o, \
					$(filter $(SRC)/$(dir)/%.c, $(SRCS)))) \
					$(patsubst %.c, (%BUILD)/%.o, main.c)

# COMPILATION
SANITIZER		=	-g3 fsanitize=address
LIBS			=	libft ft_dprintf
LFLAGS			=	-Llibs/libft -lft -Llibs/ft_dprintf -lftprintf -lreadline -lhistory
IFLAGS			=	-Iinclude -Ilibs/libft/include -Ilibs/ft_dprintf/include
MGOALS			=	$(filter-out bonus, $(MAKECMDGOALS))

.DEFAULT_GOAL	=	all

# RULES

$(BUILD):
						@$(MK) $(BUILD)

$(BUILD)/%.o:		$(SRC)/%.c $(DEPS)
						@echo "${GRAY}${CC} ${CFLAGS} ${IFLAGS} -c $< -o $@${RESET}"
						@$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

$(BUILD)/%.o:		$(SRC)/*/%.c $(DEPS)
						@echo "${GRAY}${CC} ${CFLAGS} ${IFLAGS} -c $< -o $@${RESET}"
						@$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@

$(NAME):			$(BUILD) $(DEPS) $(LIBFT) $(PRINTF)
						@echo "$(GREEN)Sources and libraries compiled.$(RESET)"
						@$(CC) $(CFLAGS) $(LFLAGS) $(IFLAGS) $(OBJS) -o $(NAME)
						@echo "$(GREEN)Build completed.$(RESET)"


all:		$(LIBS) $(NAME)


libft:
			@$(MAKE) $(MGOALS) -C $(LIBFT_DIR)

ft_dprintf:
			@$(MAKE) $(MGOALS) -C $(PRINTF_DIR)

clean:
			@echo "$(GRAY)Processing...$(RESET)"
			@$(RM) $(BUILD)
			@echo "$(GRAY)$(RM) $(BUILD)$(RESET)"
			@echo "$(RED)Cleaned object files.$(RESET)"

fclean:	clean
			@echo "$(GRAY)Processing...$(RESET)"
			@$(RM) $(NAME)
			@echo "$(GRAY)$(RM) $(NAME)$(RESET)"
			@echo "$(RED)Cleaned everything.$(RESET)"

re:		fclean all

.PHONY:	all libft ft_dprintf clean fclean re


# INCS        	=   -Iinclude
# HEADERS     	=   $(wildcard ./include/*.h) Makefile
# READ      		=   -lreadline


##LIBFT	
#LIBFT_DIR		=	libft
#LIBFT_SRCS		=	$(wildcard $(LIBFT_DIR)/*.c)
#LIBFT_OBJ		=	$(patsubst $(LIBFT_DIR)/%.c, $(OBJ_DIR)/%.o, $(LIBFT_SRCS))
##MANDATORY	
#SRC_DIR     	=   src
#OBJ_DIR     	=   obj
#SRCS     		=   $(wildcard $(SRC_DIR)/*.c)
#OBJS        	=   $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o , $(SRCS))

#.DEFAULT_GOAL	=	all

#all:    $(OBJ_DIR) $(NAME)

#$(NAME): $(OBJS) $(LIBFT_OBJ)
#	@echo "$(GREEN)Sources and Libft compiled.$(RESET)"
#	@$(CC) $(CFLAGS) $(READ) $(INCS) -o $(NAME) $(OBJS) $(LIBFT_OBJ)
#	@echo "$(GRAY)$(CC) $(CFLAGS) $(READ) $(INCS) -o $(NAME) $(OBJS) $(LIBFT_OBJ) $(RESET)"
#	@echo "$(GREEN)Build completed.$(RESET)"

#$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
#	@$(CC) $(CFLAGS) $(INCS) -c $< -o $@ $
#	@echo "$(GRAY)$(CC) $(CFLAGS) $(INCS) -c $< -o $@ $(RESET)"

#$(OBJ_DIR)/%.o: $(LIBFT_DIR)/%.c $(HEADERS)
#	@$(CC) $(CFLAGS) $(INCS) -c $< -o $@
#	@echo "$(GRAY)$(CC) $(CFLAGS) $(INCS) -c $< -o $@ $(RESET)"

#$(OBJ_DIR): $(SRC_DIR) $(LIBFT_DIR)
#	@$(MK) $(OBJ_DIR)

#%.o: %.c $(HEADERS)
#	@$(CC) $(CFLAGS) -c $< -o $@
#	@echo "$(GRAY)$(CC) $(CFLAGS) -c $< -o $@ $(RESET)"

#clean:
#	@$(RM) $(OBJ_DIR)
#	@echo "$(GRAY)$(RM) $(OBJ_DIR)$(RESET)"
#	@echo "$(RED)Cleaned$(RESET)"

#fclean:	clean
#	@$(RM) $(NAME)
#	@echo "$(GRAY)$(RM) $(NAME)$(RESET)"
#	@echo "$(RED)Fcleaned$(RESET)"

#re:			fclean all 