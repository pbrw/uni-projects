make: main.c ListOfMovies.o ListOfChildren.o tools.o InputReading.o
	@echo "Compiling main.c"
	@gcc -Wall -Wextra -std=c11 -O2 -c main.c
    
	@echo "Linking files"   
	@gcc -Wall -Wextra -std=c11 -O2 -o main main.o ListOfMovies.o ListOfChildren.o tools.o InputReading.o
    
	@echo "Done!"

ListOfMovies.o: ListOfMovies.c ListOfMovies.h tools.h
	@echo "Compiling ListOfMovies.c"
	@gcc -Wall -Wextra -std=c11 -O2 -c ListOfMovies.c

ListOfChildren.o: ListOfChildren.c ListOfChildren.h tools.h
	@echo "Compiling ListOfChildren.c"
	@gcc -Wall -Wextra -std=c11 -O2 -c ListOfChildren.c

InputReading.o: InputReading.c InputReading.h
	@echo "Compiling InputReading.c"
	@gcc -Wall -Wextra -std=c11 -O2 -c InputReading.c

tools.o: tools.c tools.h
	@echo "Compiling tools.c"
	@gcc -Wall -Wextra -std=c11 -O2 -c tools.c

clean:
	@echo "Deleting main"
	@rm main
	@echo "Deleting main.o"
	@rm main.o
	@echo "Deleting ListOfMovies.o"
	@rm ListOfMovies.o
	@echo "Deleting ListOfChildren.o"
	@rm ListOfChildren.o
	@echo "Deleting tools.o"
	@rm tools.o
	@echo "Deleting InputReading.o"
	@rm InputReading.o
	@echo "Done!"
