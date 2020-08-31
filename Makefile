NAME 	:= YouAreCute
LIBS 	:= -lsfml-graphics -lsfml-window -lsfml-system
CXX 	:= g++
CPP		:= main.cpp

all:
	$(CXX) $(CPP) -o $(NAME) $(LIBS)

clean:
	rm -rf *.o $(NAME)



