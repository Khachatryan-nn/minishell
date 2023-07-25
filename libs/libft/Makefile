# MAIN
NAME				=	libft.a
CC					=	cc
RM					=	rm -rf
MK					=	mkdir -p
AR					=	ar rcs
CFLAGS				=	-Wall -Wextra -Werror

# COLORS
GRAY				=	\033[38;5;8m
GREEN				=	\033[38;5;46m
RED					=	\033[38;5;196m
RESET				=	\033m[0m

# DEPENDENCIES
DEPS				=	libft.h Makefile

# SOURCES
SRC_DIR				=	./srcs
SRCS				=	$(wildcard $(SRC_DIR)/*.c)
BUILD				=	./build
OBJS				=	$(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))


.DEFAULT_GOAL		=	all


# RULES

$(BUILD)/%.o:	$(SRC_DIR)/%.c $(DEPS)
						$(CC) $(CFLAGS) -c $< -o $@
						@echo "$(GRAY)$(CC) $(CFLAGS) -c $< -o $@ $(RESET)"

$(NAME):			$(BUILD) $(OBJS) $(DEPS)
						@echo "$(GREEN)Sources compiled.$(RESET)"
						@$(AR) $(NAME) $(OBJS)
						@echo "$(GREEN)Build completed.$(RESET)"

$(BUILD):
						@mkdir $(BUILD)

all:	$(NAME)

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

re:		fclean $(NAME)

.PHONY:	all clean fclean re