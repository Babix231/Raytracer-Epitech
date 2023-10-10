##
## EPITEgCH PROJECT, 2023
## raytracerTest
## File description:
## Makefile
##

OBJ		=	$(SRC:.cpp=.o)

NAME_SFML	=	sfmlhandler.so

SRC_SFML	=	src/graphicals/sfml.cpp

OBJ_SFML	=	$(SRC_SFML:.cpp=.o)

LDFLAGS_SFML	=	-shared -fPIC -lsfml-graphics -lsfml-system -lsfml-window -lsfml-audio


## -------------------------------- ##


SRC_SRV		=	$(wildcard src/*.cpp)

OBJ_SRV		=	$(SRC_SRV:.cpp=.o)

NAME_SRV	=	raytracer

CC	=	g++

LDFLAGS	+= -g -lconfig++ -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

CXXFLAGS	+=	-Wall -Wextra -std=c++20

# compilation :

all:	$(NAME_SRV) $(NAME_SFML)

$(NAME_SRV):	$(OBJ_SRV)
	$(CC) -o $(NAME_SRV) $(OBJ_SRV) $(LDFLAGS) $(CXXFLAGS)

$(NAME_SFML):		$(OBJ_SFML)
			$(CXX) $(OBJ_SFML) -o $(NAME_SFML) $(LDFLAGS_SFML)
clean:
	$(RM) $(OBJ_SRV) $(OBJ_SFML)

fclean: clean
	$(RM) $(OBJ_SRV) $(NAME_SRV) $(NAME_SFML) $(OBJ_SFML)

re:		fclean all

.Phony: all clean fclean re