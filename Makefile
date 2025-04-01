main: main.o cesar.o vigenere.o utilitaires.o
	gcc main.o cesar.o vigenere.o utilitaires.o -o main

main.o: main.c cesar.h vigenere.h utilitaires.h
	gcc -c main.c -o main.o

cesar.o: cesar.c cesar.h
	gcc -c cesar.c -o cesar.o

vigenere.o: vigenere.c vigenere.h
	gcc -c vigenere.c -o vigenere.o

utilitaires.o: utilitaires.c utilitaires.h
	gcc -c utilitaires.c -o utilitaires.o

clean:
	rm -f main.o cesar.o vigenere.o utilitaires.o main

rebuild: clean main