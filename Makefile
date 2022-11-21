##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## makefile for OOP_NanotekSpice
##

SRC=	src/DLLoader.cpp	\
		src/Error.cpp \
		src/Parser.cpp	\
		src/Core.cpp	\
		src/Entity.cpp	\
		src/MenuInfo.cpp	\
		src/main.cpp	\

OBJ=	$(SRC:.cpp=.o)

NAME=	arcade

CXXFLAGS=	-std=c++11 -Iinclude -Wall -Wextra -Wshadow

LDFLAGS= -ldl

all:	core graphicals games

core:	$(OBJ)
	g++ $(OBJ) -o $(NAME) $(LDFLAGS)

games:
	make re -C games

graphicals:
	make re -C lib

clean:
	rm -f $(OBJ)
	make clean -C lib
	make clean -C games

fclean:	clean
	rm -f $(NAME)
	make fclean -C lib
	make fclean -C games

re: fclean all

.PHONY: all core games graphicals clean fclean re