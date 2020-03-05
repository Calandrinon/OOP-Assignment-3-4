#ifndef __SIGNAL_H__
#define __SIGNAL_H__

typedef struct {
    int id, priority_number;
    char modulated_signal[100];
    char type[100];
} Signal;

Signal create_signal(int id, char modulated_signal[], char type[], int priority_number);
int get_signal_id(const Signal* signal);
char* get_modulated_signal(const Signal* signal);
char* get_signal_type(const Signal* signal);
int get_signal_priority_number(const Signal* signal);

int set_signal_id(Signal* signal, int id);
char* set_modulated_signal(Signal* signal, char modulated_signal[]);
char* set_signal_type(Signal* signal, char type[]);
int set_signal_priority_number(Signal* signal, int priority_number);
void display_signal(const Signal* signal);

#endif
