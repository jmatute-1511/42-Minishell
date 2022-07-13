# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmatute- <jmatute-@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/03 17:19:28 by jmatute-          #+#    #+#              #
#    Updated: 2022/07/10 21:12:21 by jmatute-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	= 	minishell.c built_echo.c built_pwd.c built_cd.c initialize_vars.c fts_lst.c \
			ft_lst2.c ft_lst3.c built_export.c built_unset.c built_env.c list_cmds.c utils.c utils2.c expansions.c \
			quotes.c filter_list_cmds.c boleans_first_errors.c acces_cmds.c select_built.c execute.c redirects.c \
			redirects2.c

LIBFT_DIR	= libft/

OBJS	= ${SRCS:.c=.o}

NAME	= minishell

CC		= gcc 
RM		= rm -f

CFLAGS	= -Wall -Wextra -Werror #-fsanitize=address

LIBS	= -lreadline -L /Users/jmatute-/.brew/opt/readline/lib -I /Users/jmatute-/.brew/opt/readline/include



${NAME}:	${OBJS} minishell.h Makefile 
			@make -sC ${LIBFT_DIR}
			@cp ./libft/libft.a .
			@${CC} ${CFLAGS}  ${OBJS} ${LIBS} -o ${NAME} libft.a
			@echo "COMPILATION IS FINISHED"

all:		${NAME}

clean:
			@make -sC ${LIBFT_DIR} clean
			${RM} ${OBJS} libft.a

fclean:		clean
			@make -sC ${LIBFT_DIR} fclean
			${RM} ${NAME}

re:			fclean all