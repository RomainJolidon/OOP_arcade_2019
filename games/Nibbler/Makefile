##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## makefile for game
##

GAMESRC=	src/LibNibbler.cpp	\
			../../src/Entity.cpp		\
			../../src/Parser.cpp	\
			ECS/src/Instance.cpp			\
			ECS/src/ECSEntity.cpp			\
			ECS/src/MovementSystem.cpp		\
			ECS/src/InputSystem.cpp		\
			ECS/src/CollisionSystem.cpp		\
			ECS/src/FloorSystem.cpp		\
			ECS/src/FollowerSystem.cpp	\
			ECS/src/CollectibleSystem.cpp	\
			ECS/src/ClockSystem.cpp	\
			ECS/src/AiSystem.cpp

GAMEOBJ=	$(GAMESRC:.cpp=.o)

GAMENAME=	lib_arcade_nibbler.so

CXXFLAGS=	-std=c++11 -I../../include -I../ECS/include -Iinclude -Wall -Wextra -Wshadow -fPIC

all:	$(GAMEOBJ)
	g++ --shared -fPIC -o $(GAMENAME) $(GAMEOBJ)
	mv $(GAMENAME) ..

clean:
	rm -rf $(GAMEOBJ)

fclean:	clean
	rm -rf $(GAMENAME)

re: fclean all

.PHONY: all clean fclean re