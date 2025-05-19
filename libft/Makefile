# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/28 10:37:44 by jmertane          #+#    #+#              #
#    Updated: 2024/02/06 17:49:09 by jmertane         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# **************************************************************************** #
#    VARIABLES
# **************************************************************************** #

NAME := libft.a

SOURCEDIR := sources
HEADERDIR := include
BUILDDIR  := build
BUILDLOG  := build.log

# **************************************************************************** #
#    COMMANDS
# **************************************************************************** #

RM := rm -rf
AR := ar -rcs

# **************************************************************************** #
#    COMPILATION
# **************************************************************************** #

CC        := cc
CFLAGS    := -Wall -Werror -Wextra
CPPFLAGS  := -c -MMD -MP
MAKEFLAGS += --no-print-directory -j4

# **************************************************************************** #
#    SOURCES
# **************************************************************************** #

SOURCES := ft_isdigit \
           ft_strlen \
           ft_strchr \
           ft_strcmp \
           ft_atoi \
           ft_labs

SOURCES := $(addsuffix .c, $(SOURCES))

OBJECTS := $(addprefix $(BUILDDIR)/, $(SOURCES:.c=.o))

INCS := $(addprefix -I, $(HEADERDIR))

DEPS := $(OBJECTS:.o=.d)

vpath %.c $(SOURCEDIR)

# **************************************************************************** #
#    RULES
# **************************************************************************** #

all: $(NAME)

$(NAME): $(OBJECTS)
	@$(AR) $(NAME) $^
	printf "$(V)$(B)Binary:$(T)$(Y) $(NAME) $(T)\n"

re: fclean
	make all

nm:
ifneq ($(shell command -v norminette >/dev/null 2>&1 && echo 1 || echo 0), 1)
	@printf "$(R)$(B)Error: norminette: $(Y)command not found$(T)\n"; exit 1
endif
	$(foreach h, $(HEADERDIR), norminette -R CheckDefine $(h))
	$(foreach s, $(SOURCEDIR), norminette -R CheckForbiddenSourceHeader $(s))

# **************************************************************************** #
#    BUILD
# **************************************************************************** #

define build_cmd
$1/%.o: %.c | $(BUILDDIR)
	if ! $(CC) $(CFLAGS) $(CPPFLAGS) $(INCS) $$< -o $$@ 2> $(BUILDLOG); then \
		printf "$(R)$(B)\nError: \
		$(V)Unable to create object file: \
		$(R)$(B)$$@$(Y)\n\n"; \
		sed '$$d' $(BUILDLOG); exit 1 ; \
	else \
		printf "$(C)$(B)Object: $(G)$$@ $(T)\n"; \
	fi
endef

# **************************************************************************** #
#    CLEAN
# **************************************************************************** #

clean:
	$(call delete_cmd, $(BUILDDIR), $(BUILDLOG))

fclean: clean
	$(call delete_cmd, $(NAME))

define delete_cmd
	printf "$(R)$(B)Delete:$(T)$(Y)$1$2$3$4$5$(T)\n"
	$(RM) $1 $2 $3 $4 $5
endef

# **************************************************************************** #
#    COLORS
# **************************************************************************** #

T = \033[0m
B = \033[1m
G = \033[32m
V = \033[35m
C = \033[36m
Y = \033[33m
R = \033[31m

# **************************************************************************** #
#    UTILS
# **************************************************************************** #

-include $(DEPS)

$(BUILDDIR):
	mkdir -p $@

$(foreach build, $(BUILDDIR), $(eval $(call build_cmd, $(build))))

# **************************************************************************** #
#    PHONY
# **************************************************************************** #

.PHONY: all re nm
.PHONY: clean fclean

.SILENT:
