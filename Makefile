NAME = expert-system
FLAGS = -std=c++11 -Wall -Wextra -Werror -g


INCLUDE = -I includes \
		-I includes/Class \
		-I includes/Enums \
		-I includes/Exceptions \
		-I includes/Libs \
		-I includes/Utils \
		-I ${HOME}/.brew/Cellar/sdl2/2.0.8/include/ \
		-I ${HOME}/.brew/Cellar/glew/2.1.0/include

SRCSPATH = srcs/

SRCS = 	main.cpp \
		Utils/Color.cpp \
		Utils/Logger.cpp \
		Utils/Reader.cpp \
		Class/SDLDisplay.cpp \
		Class/SystemManager.cpp \
		Class/Fact.cpp \
		Class/Rule.cpp \
		Enums/EFactStatus.cpp \
		Enums/EStep.cpp \
		Exceptions/LoopException.cpp \
		Exceptions/ConflictException.cpp \
		Exceptions/ParseErrorException.cpp

LIBS =  -L ${HOME}/.brew/Cellar/sdl2/2.0.8/lib/ -lSDL2 \
		-L ${HOME}/.brew/Cellar/glew/2.1.0/lib -lGLEW \
		-framework OpenGL -lm  

OBJ= $(SRC:.cpp=.o)

CC = clang++

SRC = $(addprefix $(SRCSPATH), $(SRCS))

%.o: %.cpp
	$(CC) $(INCLUDE) -c $(FLAGS)  $< -o $@ 

all: $(NAME)

$(NAME): $(OBJ)
	$(CC)  $(FLAGS) $(INCLUDE) -o $(NAME) $(LIBS) $(OBJ) 

clean:
	rm -f $(OBJ)

fclean:
	rm -f $(NAME) $(OBJ)

re: fclean all

.PHONY: all clean fclean re
