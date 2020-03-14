#ifndef __REPOSITORY_H__
#define __REPOSITORY_H__
#include "signal.h"

typedef struct {
    Signal *signals;
    int number_of_elements, array_size;
} SignalContainer;

typedef struct {
    char** commands;
    int number_of_elements, array_size;
} UndoStack;

typedef struct {
    SignalContainer container;
} SignalRepository;

UndoStack create_undo_stack();
void push_command(UndoStack* undo_stack, char* command);
char* pop_command(UndoStack* undo_stack);
SignalRepository create_repository();
void add_signal(SignalRepository *repository, int id, char modulated_signal[], char type[], int priority_number);
void delete_signal_by_id(SignalRepository *repository, int signal_id);
void update_signal(SignalRepository *repository, int id, char new_modulated_signal[], char new_type[], int new_priority_number);
SignalContainer get_signal_container(const SignalRepository *repository);
Signal search_signal(SignalRepository *repository, int signal_id);
void free_repository(SignalRepository* repository);
void free_undo_stack(UndoStack* undo_stack);

#endif
