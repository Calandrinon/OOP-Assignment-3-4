#include <string.h>
#include <stdio.h>
#include "signal.h"
#include <stdlib.h>

Signal create_signal(int id, char modulated_signal[], char type[], int priority_number) {
    Signal signal;

    signal.id = id;
    signal.priority_number = priority_number;
    strcpy(signal.modulated_signal, modulated_signal);
    strcpy(signal.type, type);

    return signal;
}


int get_signal_id(const Signal* signal) {
    return signal->id;
}


char* get_modulated_signal(const Signal* signal) {
    return (char*)signal->modulated_signal;
}


char* get_signal_type(const Signal* signal) {
    return (char*)signal->type;
}


int get_signal_priority_number(const Signal* signal) {
    return signal->priority_number;
}


char* get_signal_as_string(Signal* signal) {
    char* str = (char*)malloc(55*sizeof(char));            /// POSSIBLE MEMORY LEAK
    char* priority_number = (char*)malloc(5*sizeof(char)); /// POSSIBLE MEMORY LEAK
    sprintf(str, "%d", signal->id);
    str = strcat(str, " ");
    str = strcat(str, signal->modulated_signal);
    str = strcat(str, " ");
    str = strcat(str, signal->type);
    str = strcat(str, " ");
    sprintf(priority_number, "%d", signal->priority_number);
    str = strcat(str, priority_number);
    free(priority_number);

    return str;
}


void set_signal_id(Signal* signal, int id) {
    signal->id = id;
}


void set_modulated_signal(Signal* signal, char modulated_signal[]) {
    strcpy(signal->modulated_signal, modulated_signal);
}


void set_signal_type(Signal* signal, char type[]) {
    strcpy(signal->type, type);
}


void set_signal_priority_number(Signal* signal, int priority_number) {
    signal->priority_number = priority_number;
}


void display_signal(const Signal* signal) {
    printf("ID: %d; Modulated signal: %s; Type: %s; Priority number: %d\n", signal->id, signal->modulated_signal, signal->type, signal->priority_number);
}
