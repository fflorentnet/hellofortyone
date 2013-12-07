usine : main.o robot.o
	gcc main.o robot.o -o usine -lpthread

main.o : main.c robot.c
	gcc -c main.c -o main.o -lpthread

robot.o : robot.c
	gcc -c robot.c -o robot.o -lpthread
