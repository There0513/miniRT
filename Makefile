# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: threiss <threiss@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/12 16:58:09 by threiss           #+#    #+#              #
#    Updated: 2021/08/26 10:48:18 by threiss          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS_PATH	=	./srcs/

SRCS_NAMES	=	main.c \
			utils.c \
			utils2.c \
			get_next_line.c \
			parsing/parse.c \
			parsing/parse2.c \
			parsing/parsing_check.c \
			parsing/parsing_check1.c \
			parsing/parsing_check_objs.c \
			parsing/parsing_add_objs.c \
			parsing/parsing_add.c \
			parsing/utils_parsing.c \
			utils_keypress.c \
			ft_split.c \
			lib.c \
			lib2.c \
			math.c \
			math2.c \
			find_closest.c \
			intersections.c \
			light.c \
			shades.c \
			
INCL	=	./includes/

NAME	= 	miniRT

CC	=	clang

RM	=	rm -f

CFLAGS	=	-Wall -Wextra -Werror

SRCS	=	$(addprefix $(SRCS_PATH), $(SRCS_NAMES))

OBJS	=	${SRCS:.c=.o}

.c.o:
		@${CC} ${CFLAGS} -I$(INCL) -I./mlx_linux/ -c $< -o ${<:.c=.o}

$(NAME):	${OBJS}
		@make --silent -C ./mlx_linux/
		@${CC} ${CFLAGS} ${OBJS} mlx_linux/libmlx.a -L/mlx_linux -L/usr/lib -Imlx_linux -I$(INCL) -lXext -lX11 -lm -o ${NAME}

all:		${NAME}

clean:
		${RM} ${OBJS}

fclean:		clean
		${RM} ${NAME}

re:		fclean all

.PHONY:
		all clean fclean re
