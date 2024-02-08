# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmertane <jmertane@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/09 15:57:04 by jmertane          #+#    #+#              #
#    Updated: 2024/02/08 16:22:51 by jmertane         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	libftprintf.a
LIBDR	=	./libft/
LIBNM	=	libft.a

RM		= 	rm -rf
AR		= 	ar -r
CFLAGS	= 	-Wall -Werror -Wextra

SRCS 	=	ft_printf.c \
			ft_printf_fmt.c

OBJS 	=	$(SRCS:.c=.o)

all: $(NAME)

$(NAME): libft $(OBJS)
	@$(AR) $(NAME) $(OBJS)

libft:
	@make -C $(LIBDR)
	@cp $(LIBDR)$(LIBNM) .
	@mv $(LIBNM) $(NAME)

clean:
	$(RM) $(OBJS)
	@make -C $(LIBDR) clean

fclean: clean
	$(RM) $(NAME) $(LIBDR)$(LIBNM)

re: fclean all

.PHONY: all libft clean fclean re
