FLAGS = -ansi -Werror -Wall -Wextra
OBJs = main.o linkedlist.o things.o

all: $(OBJs)
	gcc $^ -o guesser

$(OBJs): %.o: %.c
	gcc -c $^ -o $@ $(FLAGS)

clean:
	rm *.o guesser
