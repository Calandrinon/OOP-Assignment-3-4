#ifndef __REPOSITORY_H__
#define __REPOSITORY_H__
#include "signal.h"

typedef struct {
    Signal signals[500];
    int size;
} SignalContainer;

typedef struct {
    SignalContainer container;
} SignalRepository;

SignalRepository create_repository();
void add_signal(SignalRepository *repository, int id, char modulated_signal[], char type[], int priority_number);
void delete_signal_by_id(SignalRepository *repository, int signal_id);
void update_signal(SignalRepository *repository, int id, char new_modulated_signal[], char new_type[], int new_priority_number);
SignalContainer get_signal_container(const SignalRepository *repository);
#endif
