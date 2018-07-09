# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: otimofie <otimofie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/06/19 22:00:20 by otimofie          #+#    #+#              #
#    Updated: 2018/06/24 17:56:50 by dburtnja         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Name of the program.
NAME     = ft_retro

# Sources and objects.
SRCS     = Board.cpp Bullet.cpp Enemy.cpp Player.cpp Space_object.cpp Window.cpp main.cpp Asteroid.cpp Boss.cpp
OBJS     = $(SRCS:.cpp=.o)

# Define all the compiling flags.
CXX      = clang++ 
CXXFLAGS = -std=c++98 

# Compile and create everything.
all: $(NAME)

# Compile the program with the objects.
$(NAME): $(OBJS)
	@$(CXX) $(OBJS) -lncurses -o $@

# This won't run if the source files don't exist or are not modified.
%.o: %.cpp 
	$(CXX) $(CXXFLAGS) -o $@ -c $<

# Rule to remove all the object files.
clean:
	@rm -f $(OBJS)
	@rm -f *.gch
	@echo "[INFO] Objects removed!"

# Rule to remove everything that has been created by the makefile.
fclean: clean
	@rm -f $(NAME)
	@echo "[INFO] $(NAME) removed!"

# Rule to re-make everything.
re:     fclean all

# Makes sure that gnu make will still run even if files called
# clean / fclean / all and re already exist in the directory
.PHONY: all clean fclean re
