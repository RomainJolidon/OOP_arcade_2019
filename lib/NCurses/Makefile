##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## makefile for NCurses Graphic Library
##

LIBNCSRC=	../../src/MenuInfo.cpp \
			src/MenuNCurses.cpp \
			src/LibNCurses.cpp \


LIBNCOBJ=	$(LIBNCSRC:.cpp=.o)

LIBNCNAME=	lib_arcade_NCurses.so

CXXFLAGS=	-std=c++11 -I../../include -Iinclude -Wall -Wextra -Wshadow -fPIC

LIBFLAGS=	-lncurses

all:	$(LIBNCOBJ)
	g++ --shared -fPIC -o $(LIBNCNAME) $(LIBNCOBJ) $(LIBFLAGS)
	mv $(LIBNCNAME) ..

clean:
	rm -rf $(LIBNCOBJ)

fclean:	clean
	rm -rf $(LIBNCNAME)

re: fclean all

.PHONY: all clean fclean re