# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tpotier <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/04/01 16:36:41 by tpotier           #+#    #+#              #
#    Updated: 2019/05/02 19:58:52 by tpotier          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
FILES1 = checker
IFILES1 = checker.h
FILES2 = push_swap
IFILES2 = push_swap.h
NAME1 = checker
NAME2 = push_swap
IDIR = incs/
SDIR = srcs/
LIBFTDIR = libft/
LIBFT = $(LIBFTDIR)libft.a
LIBFTINC = $(LIBFTDIR)incs/
CFLAGS = -Wall -Wextra -Werror -I$(IDIR) -I$(LIBFTINC) -MMD -MP
CFLAGSF = $(CFLAGS) -L$(LIBFTDIR) -lft


SRCS1 = $(addprefix $(SDIR), $(addsuffix .c, $(FILES1)))
INCS1 = $(addprefix $(IDIR), $(IFILES1))
OBJS1 = $(SRCS1:.c=.o)
DEPS1 = $(SRCS1:.c=.d)
SRCS2 = $(addprefix $(SDIR), $(addsuffix .c, $(FILES2)))
INCS2 = $(addprefix $(IDIR), $(IFILES2))
OBJS2 = $(SRCS2:.c=.o)
DEPS2 = $(SRCS2:.c=.d)

all: $(NAME1) $(NAME2)

$(LIBFT):
	make -C $(LIBFTDIR)

$(NAME1): $(OBJS1) $(LIBFT)
	$(CC) $(CFLAGSF) -o $@ $(OBJS1)

$(NAME2): $(OBJS2) $(LIBFT)
	$(CC) $(CFLAGSF) -o $@ $(OBJS2)

%.o: %.c
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	make -C $(LIBFTDIR) $@
	rm -f $(OBJS1) $(OBJS2) $(DEPS)

fclean: clean
	make -C $(LIBFTDIR) $@
	rm -f $(NAME1) $(NAME2)

re: fclean all

.PHONY: all clean fclean re
-include $(DEPS)
