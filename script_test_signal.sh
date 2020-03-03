gcc -c main.c
gcc -c signal.c
gcc -o main *.o
./main
rm *.o
rm main
