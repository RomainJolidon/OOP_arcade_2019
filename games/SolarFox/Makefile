##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## makefile for game
##

GAMESRC=	src/LibSolar.cpp	\
			../../src/Entity.cpp		\
			ECS/src/Instance.cpp			\
			ECS/src/ECSEntity.cpp			\
			ECS/src/MovementSystem.cpp		\
			ECS/src/InputSystem.cpp		\
			ECS/src/CollisionSystem.cpp		\
			ECS/src/FloorSystem.cpp \
			ECS/src/CollectibleSystem.cpp \
			ECS/src/ShootingSystem.cpp \
			ECS/src/ClockSystem.cpp \

GAMEOBJ=	$(GAMESRC:.cpp=.o)

GAMENAME=	lib_arcade_solarfox.so

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