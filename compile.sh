gcc -Wall -g -c main.c
gcc -Wall -g -c signal.c
gcc -Wall -g -c repository.c
gcc -Wall -g -c service.c
gcc -Wall -g -c ui.c
gcc -Wall -g -c tests.c
gcc -Wall -g -O0 -o main *.o

