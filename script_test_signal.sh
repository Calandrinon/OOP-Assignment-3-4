gcc -c main.c
gcc -c signal.c
gcc -c repository.c
gcc -c tests.c
gcc -o main *.o
./main
rm *.o
rm main
