# MAIN
NAME			=	minishell
CC				=	cc
RM				=	rm -rf
MK				=	mkdir -p
CFLAGS			=	-Wall -Wextra -Werror

# COLORS
GRAY			=	\033[38;5;8m
GREEN			=	\033[38;5;46m
RED				=	\033[38;5;196m
RESET			=	\033[0m

# LIBRARIES
PREFIX			=	$(shell pwd)/rd_lib
LIBFT_DIR		=	./libs/libft
LIBFT			=	$(LIBFT_DIR)/libft.a
PRINTF_DIR		=	./libs/ft_dprintf
PRINTF			=	$(PRINTF_DIR)/libftdprintf.a
GNL_DIR			=	./libs/get_next_line
GNL				=	$(GNL_DIR)/get_next_line.a
INCS_DIR		=	./include

# DEPENDENCIES
DEPS			=	$(wildcard $(INCS_DIR)/*.h) Makefile

# SOURCES
SRC_DIR			=	./src
BUILD			=	./build
SUBDIRS			=	lexer parser utils executer builtins wildcardAndExpand
SRCDIRS			:=	$(addprefix $(SRC_DIR)/, $(SUBDIRS))
SRCS			:=	$(notdir $(foreach dir, $(SRCDIRS), $(wildcard $(dir)/*.c))) $(notdir $(SRC_DIR)/main.c)

# OBJECTS
OBJS			:=	$(patsubst %.c, $(BUILD)/%.o, $(SRCS))

# COMPILATION
SANITIZER		=	-g3 -fsanitize=address
LIBS			=	libft ft_dprintf gnl
LFLAGS			=	-L$(LIBFT_DIR) -lft -L$(PRINTF_DIR) -lftdprintf -L$(GNL_DIR) -lgnl -lreadline -L./rd_lib/lib
IFLAGS			=	-Iinclude -I$(LIBFT_DIR)/include -I$(PRINTF_DIR)/include -I$(GNL_DIR)/include -I./rd_lib/include
MGOALS			=	$(filter-out bonus, $(MAKECMDGOALS))

.DEFAULT_GOAL	=	all

# PROGRESS BAR
TOTAL_SRCS		:= $(words $(SRCS))
COMPILED_SRCS	:= 0

define update_progress
		$(eval COMPILED_SRCS := $(shell echo \
			$$(( $(COMPILED_SRCS) +1)) ))
		$(eval PERCENTAGE := $(shell echo \
			$$(( $(COMPILED_SRCS) * 100 / $(TOTAL_SRCS) )) ))
		@printf "${GREEN}\rBuilding : ["
		@printf "%-*s" $$(($(PERCENTAGE) / 2)) "" | tr ' ' ░
		@printf "\r%-*s" $$((7)) "" | tr ' ' '\t'
		@printf "] (%d%%)$(RESET)" $(PERCENTAGE)
endef

# RULES

$(BUILD):
						@$(MK) $(BUILD)
						@echo "${GREY}Building minishell...${RESET}"

$(BUILD)/%.o:		$(SRC_DIR)/%.c $(DEPS)
						@$(CC) $(CFLAGS) $(SANITIZER) $(IFLAGS) -c $< -o $@
						$(call update_progress)

$(BUILD)/%.o:		$(SRC_DIR)/*/%.c $(DEPS)
						@$(CC) $(CFLAGS) $(SANITIZER) $(IFLAGS) -c $< -o $@
						$(call update_progress)

$(NAME):			$(BUILD) $(OBJS) $(LIBFT) $(PRINTF)
						@echo "$(GREEN)\nSources and libraries compiled.$(RESET)"
						@$(CC) $(CFLAGS) $(SANITIZER) $(LFLAGS) $(IFLAGS) $(OBJS) -o $(NAME)
						@echo "$(GREEN)Build completed.$(RESET)"


all:		$(LIBS) $(NAME)

libft:
			@$(MAKE) $(MGOALS) -C $(LIBFT_DIR)

ft_dprintf:
			@$(MAKE) $(MGOALS) -C $(PRINTF_DIR)

gnl:
			@$(MAKE) $(MGOALS) -C $(GNL_DIR)

clean:
			@echo "$(GRAY)Processing...$(RESET)"
			@$(RM) $(BUILD)
			@$(MAKE) clean -C $(LIBFT_DIR)
			@$(MAKE) clean -C $(PRINTF_DIR)
			@$(MAKE) clean -C $(GNL_DIR)
			@echo "$(RED)Cleaned object files.$(RESET)"

fclean:	clean
			@echo "$(GRAY)Processing...$(RESET)"
			@$(RM) $(NAME) $(NAME)_old "$(NAME) "* 2> /dev/null || :
			@$(RM) */*\ 2* */*\ 3* */*\ 4* */*/*\ 2* */*/*\ 3* */*/*\ 4* 2> /dev/null || :
			@$(MAKE) fclean -C $(LIBFT_DIR)
			@$(MAKE) fclean -C $(PRINTF_DIR)
			@$(MAKE) fclean -C $(GNL_DIR)
			@echo "$(RED)Cleaned everything.$(RESET)"

readline:
			cd readline-master && make clean && ./configure --prefix=$(PREFIX) && make && make install	

re:		fclean all

.PHONY: all libft ft_dprintf gnl clean fclean re update_progress readline bash
