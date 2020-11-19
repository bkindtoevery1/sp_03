minish : get_cmd.o print_sigint.o shell.o main.o
	g++ get_cmd.o print_sigint.o shell.o main.o -o minish
	make clean

get_cmd.o : get_cmd.cpp minish.h
	g++ -c get_cmd.cpp

print_sigint.o : print_sigint.h print_sigint.cpp minish.h
	g++ -c print_sigint.cpp

shell.o : shell.h shell.cpp minish.h
	g++ -c shell.cpp

main.o : main.cpp minish.h
	g++ -c main.cpp

clean :
	rm -f *.o