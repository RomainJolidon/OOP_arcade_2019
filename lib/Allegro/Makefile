##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## makefile for Sfml Graphic Graphic Library
##

LIBALSRC=	../../src/MenuInfo.cpp	\
			src/LibAllegro.cpp	\
			src/MenuAllegro.cpp


LIBALOBJ=	$(LIBALSRC:.cpp=.o)


LIBALNAME=	lib_arcade_Allegro.so

CXXFLAGS=	-std=c++11 -I../../include -Iinclude -I/usr/local/include/allegro5 -Wall -Wextra -Wshadow -fPIC

LIBFLAGS= -L/usr/local/lib -lallegro -lallegro_ttf -lallegro_font -lallegro_primitives

all:	$(LIBALOBJ)
	g++ --shared -fPIC -o $(LIBALNAME) $(LIBALOBJ) $(LIBFLAGS)
	mv $(LIBALNAME) ..

clean:
	rm -rf $(LIBALOBJ)

fclean:	clean
	rm -rf $(LIBALNAME)

re: fclean all

.PHONY: all clean fclean re