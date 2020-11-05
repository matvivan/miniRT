# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: matvivan <matvivan@student.42.us.org>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/14 20:11:24 by matvivan          #+#    #+#              #
#    Updated: 2020/11/04 19:32:35 by matvivan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT
SRC = main.c math_3d.c object_camera.c object_sphere.c bitmap.c
INC = -Imlx/ -Ilibft/
CFLAGS = -Wall -Wextra -Werror -g
LFTFLAGS = -Llibft -lft
MLXFLAGS = -Lmlx -lmlx -framework OpenGL -framework AppKit

.PHONY: all clean fclean re bonus

all: $(NAME)

$(NAME): $(SRC)
	@$(MAKE) -C mlx -s CFLAGS+=-w
	@$(MAKE) -C libft -s
	@$(CC) $(CFLAGS) -c $(SRC) $(INC)
	@$(CC) $(SRC:.c=.o) -o $(NAME) $(LFTFLAGS) $(MLXFLAGS)

clean:
	@$(MAKE) clean -C mlx -s
	@echo "make: 'libmlx.a' dir cleaned."
	@$(MAKE) fclean -C libft
	@$(RM) $(SRC:.c=.o)
	@echo "make: '$(NAME)' dir cleaned."

fclean: clean
	@$(RM) $(NAME)
	@echo "make: '$(NAME)' deleted."

re: fclean all

bonus: re