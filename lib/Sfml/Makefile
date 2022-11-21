##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## makefile for Sfml Graphic Graphic Library
##

LIBSFSRC=	../../src/MenuInfo.cpp	\
			src/LibSfml.cpp	\
			src/MenuSfml.cpp


LIBSFOBJ=	$(LIBSFSRC:.cpp=.o)


LIBSFNAME=	lib_arcade_SFML.so

CXXFLAGS=	-std=c++11 -I../../include -Iinclude -Wall -Wextra -Wshadow -fPIC

LIBFLAGS=	-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

all:	$(LIBSFOBJ)
	g++ --shared -fPIC -o $(LIBSFNAME) $(LIBSFOBJ) $(LIBFLAGS)
	mv $(LIBSFNAME) ..

clean:
	rm -rf $(LIBSFOBJ)

fclean:	clean
	rm -rf $(LIBSFNAME)

re: fclean all

.PHONY: all clean fclean re