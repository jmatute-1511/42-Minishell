# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmatute- <jmatute-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/03 17:19:28 by jmatute-          #+#    #+#              #
#    Updated: 2022/05/20 15:43:04 by jmatute-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=  minishell.c built_echo.c built_pwd.c built_cd.c initialize_vars.c fts_lst.c ft_lst2.c built_export.c built_unset.c built_env.c list_cmds.c#parse_comand_line.c

LIBFT_DIR	= libft/

OBJS	= ${SRCS:.c=.o}

NAME	= minishell

CC		= gcc 
RM		= rm -f

CFLAGS	= -Wall -Wextra -Werror -lreadline#-fsanitize=address

.c.o: ${SRCS}
			@${CC}  -c $< -o ${<:.c=.o}

${NAME}:	${OBJS} minishell.h Makefile 
			@make -sC ${LIBFT_DIR}
			@cp ./libft/libft.a .
			@${CC} ${CFLAGS}  ${OBJS} -o ${NAME} libft.a
			@echo "COMPILATION IS FINISHED"

all:		${NAME}

clean:
			@make -sC ${LIBFT_DIR} clean
			${RM} ${OBJS} libft.a

fclean:		clean
			@make -sC ${LIBFT_DIR} fclean
			${RM} ${NAME}

re:			fclean all