gcc -Wall -c main.c
gcc -Wall -c signal.c
gcc -Wall -c repository.c
gcc -Wall -c service.c
gcc -Wall -c ui.c
gcc -Wall -c tests.c
gcc -Wall -g -o main *.o
./main
rm *.o
rm main
