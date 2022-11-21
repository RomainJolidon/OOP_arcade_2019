##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## makefile for OOP_NanotekSpice
##

all:
	make -C Pacman
	make -C Nibbler
	make -C SolarFox
	make -C Centipede
	make -C Qix

clean:
	make clean -C Pacman
	make clean -C SolarFox
	make clean -C Nibbler
	make clean -C Centipede
	make clean -C Qix

fclean:	clean
	make fclean -C Pacman
	make fclean -C Nibbler
	make fclean -C SolarFox
	make fclean -C Centipede
	make fclean -C Qix
	rm -rf *.so

re: fclean all

.PHONY: all clean fclean re