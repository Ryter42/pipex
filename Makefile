# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: emoreau <emoreau@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/29 19:25:41 by emoreau           #+#    #+#              #
#    Updated: 2023/09/25 13:29:04 by emoreau          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_DIR		=	./srcs/
BONUS_SRC_DIR		=	./srcs_bonus/
OBJ_DIR		=	./obj/
BONUS_OBJ_DIR		=	./bonus_obj/
SRCS		=	pipex.c\
				exec.c\
				path.c\
				free.c\
				here_doc.c
SRCS_BONUS	=	pipex_bonus.c\
				exec_bonus.c\
				path_bonus.c\
				free_bonus.c\
				here_doc_bonus.c

OBJS = $(patsubst %.c,$(OBJ_DIR)%.o,$(SRCS))
BONUS_OBJS = $(patsubst %.c,$(BONUS_OBJ_DIR)%.o,$(SRCS_BONUS))

NAME	=	pipex
CC		=	gcc
CFLAGS	=	-Wall -Wextra -Werror -g3
RM		=	rm -rf

all:	${NAME}

$(NAME):	$(OBJS)
	$(MAKE) -C libft
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) libft/libft.a

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

bonus:	$(BONUS_OBJS)
	$(MAKE) -C libft
	$(CC) $(CFLAGS) -o $(NAME) $(BONUS_OBJS) libft/libft.a

$(BONUS_OBJ_DIR)%.o: $(BONUS_SRC_DIR)%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	${RM} $(OBJ_DIR) $(BONUS_OBJ_DIR)
	$(MAKE) -C libft clean

fclean:	clean
		${RM} ${NAME}
		$(MAKE) -C libft fclean

re:		fclean all

.PHONY: 	all clean fclean re