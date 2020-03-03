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

#endif
