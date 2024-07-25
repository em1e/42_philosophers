# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vkettune <vkettune@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/21 12:56:28 by vkettune          #+#    #+#              #
#    Updated: 2024/07/25 12:27:38 by vkettune         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
HEADERS = -I ./incs/
FLAGS = -Wall -Wextra -Werror -g -pthread $(HEADERS)

OBJS_DIR = objs/
SRCS_DIR = srcs/

FILES = error_handling.c \
				init.c \
				main.c \
				philo_action.c \
				philo_monitor.c \
				philo_start.c \
				utils.c \
				check.c \

SOURCES = $(addprefix $(SRCS_DIR), $(FILES))

OBJECTS = $(addprefix $(OBJS_DIR), $(FILES:.c=.o))

all: folders $(NAME)
	@echo "- - - - - - - - - - - - - - - - - - - - - - -"
	@echo "Run the program with ./$(NAME)"

objs/%.o: srcs/%.c
	@cc $(FLAGS) -c $< -o $@ && echo "Compiled: $@"

$(NAME): $(OBJECTS)
	@cc $(OBJECTS) $(FLAGS) -o $(NAME)
	@echo "- - - - -  ✨ Philosophers compiled ✨ - - - - -"

folders:
	@echo "- - - - -  📦 Creating folders 📦 - - - - - -"
	@mkdir -p objs/

clean:
	@rm -rf objs/
	@echo "- - - - -❗All object files cleaned❗- - - - -"
	
fclean: clean
	@rm -rf objs/
	@rm -f $(NAME)
	@echo "- - - -❗All executable files cleaned❗- - - -"
	
re: fclean all
	@echo "Sucessfully cleaned and rebuilt everything"

.PHONY: all clean fclean re


.PHONY:	all clean fclean re