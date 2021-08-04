# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: threiss <threiss@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/12 16:58:09 by threiss           #+#    #+#              #
#    Updated: 2021/08/02 17:14:19 by threiss          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS_PATH	=	./srcs/

SRCS_NAMES	=	main.c \
			utils.c \
			utils_struct.c \
			get_next_line.c \
			parse.c \
			parsing_check.c \
			lib.c \
			find_closest.c \
			sphere.c \
		#	camera.c \

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

#bonus
.PHONY:
		all clean fclean re