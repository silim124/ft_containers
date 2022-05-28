# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: silim <silim@student.42seoul.kr>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/05/28 15:44:43 by silim             #+#    #+#              #
#    Updated: 2022/05/28 15:48:32 by silim            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_containers
SRCS_FOLDER	= ./tester/
SRCS			=	main.cpp
FLAGS 			= -Wall -Wextra -Werror --std=c++98

OBJS_FOLDER 	= ./tester/obj/

OBJ			= $(SRCS:.cpp=.o)
OBJS		 	= $(addprefix $(OBJS_FOLDER), $(OBJ));

$(OBJS_FOLDER)%.o :	$(SRCS_FOLDER)%.cpp
	@mkdir -p	$(OBJS_FOLDER)
	@echo "Compiling: $<"
	@clang++ $(FLAGS) -c $< -o $@

$(NAME): $(OBJS)
	@clang++ $(FLAGS) -o $(NAME) $(OBJS)

all: $(NAME)

clean:
		@echo "Cleaning previous objs: $(OBJS_FOLDER)"
		@rm -rf $(OBJS)

fclean: clean
		@echo "Cleaning bins: $(NAME)"
		@rm -f $(NAME) ft_containers

re: fclean all

run: $(NAME)
	@./$(NAME)
