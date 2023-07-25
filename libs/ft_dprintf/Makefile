# MAIN
NAME				=	libftdprintf.a
CC					=	cc
AR					=	ar rcs
RM					=	rm -rf
MK					=	mkdir -p
CFLAGS				=	-Wall -Wextra -Werror
IFLAGS				=	-Iinclude

# COLORS
GRAY				=	\033[38;5;8m
GREEN				=	\033[38;5;46m
RED					=	\033[38;5;196m
RESET				=	\033m

# DEPENDENCIES
DEPS				=	include/ft_dprintf.h Makefile

# SOURCES
SRC_DIR				=	./srcs
SRCS				=	$(wildcard $(SRC_DIR)/*.c)
BUILD				=	./build
OBJS				=	$(patsubst $(SRC_DIR)/%.c, $(BUILD)/%.o, $(SRCS))

.DEFAULT_GOAL		=	all

# PROGRESS BAR
TOTAL_SRCS := $(words $(SRCS))
COMPILED_SRCS := 0

define update_progress
	$(eval COMPILED_SRCS := $(shell echo $$(($(COMPILED_SRCS)+1))))
	$(eval PERCENTAGE := $(shell echo $$(($(COMPILED_SRCS)*100/$(TOTAL_SRCS)))))
	@printf "${GRAY}\rBuilding : ["
	@printf "%-*s" $$(($(PERCENTAGE) / 2)) "" | tr ' ' ░
	@printf "\r%-*s" $$((7)) "" | tr ' ' '\t'
	@printf "] (%d%%)$(RESET)" $(PERCENTAGE)
endef

# RULES

$(BUILD)/%.o:		$(SRC_DIR)/%.c $(DEPS)
						@$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@
						$(call update_progress)
#						@echo "$(GRAY)$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@$(RESET)"

$(NAME):			$(BUILD) $(OBJS) $(DEPS)
						@cp -f $(NAME) $(NAME)_old 2> /dev/null || :
						@$(AR) $(NAME) $(OBJS)
						@echo "\n$(GRAY)dprintf build completed.$(RESET)"

$(BUILD):
						@mkdir $(BUILD)
						@echo "${GRAY}Building dprintf...${RESET}"

all:	$(NAME)

clean:
			@$(RM) $(BUILD)
			@echo "$(GRAY)Cleaned dprintf build.$(RESET)"

fclean:	clean
			@$(RM) $(NAME)
			@echo "$(GRAY)Cleaned everything in dprintf.$(RESET)"

re:		fclean $(NAME)

.PHONY:	all clean fclean re update_progress