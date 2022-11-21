##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## makefile for OOP_NanotekSpice
##

all:
	make -C NCurses
	make -C Sfml
	make -C Allegro

clean:
	make clean -C NCurses
	make clean -C Sfml
	make clean -C Allegro

fclean:	clean
	make fclean -C NCurses
	make fclean -C Sfml
	make fclean -C Allegro
	rm -rf *.so

re: fclean all

.PHONY: all clean fclean re