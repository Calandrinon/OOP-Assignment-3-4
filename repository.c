#include "repository.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

SignalRepository create_repository() {
    SignalRepository repository;
    repository.container.number_of_elements = 0;
    repository.container.array_size = 2;
    repository.container.signals = (Signal*)malloc(repository.container.array_size*sizeof(Signal));

    return repository;
}


void add_signal(SignalRepository *repository, int id, char modulated_signal[], char type[], int priority_number) {
    if (repository->container.number_of_elements == repository->container.array_size) {
        int new_signals_array_size = repository->container.array_size * 2;
        Signal* new_signals_array = (Signal*)malloc(new_signals_array_size*sizeof(Signal));

        for (int i = 0; i < repository->container.number_of_elements; i++) {
            new_signals_array[i] = repository->container.signals[i];
        }

        repository->container.array_size = new_signals_array_size;
        free(repository->container.signals);
        repository->container.signals = new_signals_array;
        //printf("New size of the repository container: %d\n", new_signals_array_size);
    }

    for (int i = 0; i < repository->container.number_of_elements; i++) {
        if (repository->container.signals[i].id == id) {
            printf("No!\n");
            return;
        }
    }

    int number_of_elements = repository->container.number_of_elements;
    repository->container.signals[number_of_elements] = create_signal(id, modulated_signal, type, priority_number);
    repository->container.number_of_elements++;
}


void delete_signal_by_id(SignalRepository *repository, int signal_id) {
    int id_found = 0;

    for (int i = 0; i < repository->container.number_of_elements; i++) {
        if (repository->container.signals[i].id == signal_id)
            id_found = 1;

        if (id_found)
            repository->container.signals[i] = repository->container.signals[i+1];
    }

    if (id_found)
        repository->container.number_of_elements--;
    else
        printf("No!\n");
}


void update_signal(SignalRepository *repository, int id, char new_modulated_signal[], char new_type[], int new_priority_number) {
    for (int i = 0; i < repository->container.number_of_elements; i++) {
        if (repository->container.signals[i].id == id) {
            set_modulated_signal(&(repository->container.signals[i]), new_modulated_signal);
            set_signal_type(&(repository->container.signals[i]), new_type);
            set_signal_priority_number(&(repository->container.signals[i]), new_priority_number);
            return;
        }
    }
}


Signal search_signal(SignalRepository *repository, int signal_id) {

    for (int i = 0; i < repository->container.number_of_elements; i++) {
        if (repository->container.signals[i].id == signal_id)
            return repository->container.signals[i];
    }

    Signal signal = create_signal(-1, "-1", "-1", -1);
    return signal;
}


SignalContainer get_signal_container(const SignalRepository *repository) {
    return repository->container;
}


void free_repository(SignalRepository* repository) {
    free(repository->container.signals);
}

UndoStack create_undo_stack() {
    UndoStack undo_stack;
    undo_stack.number_of_elements = 0;
    undo_stack.array_size = 4;
    undo_stack.commands = (char**)malloc(undo_stack.array_size*sizeof(char*));

    return undo_stack;
}


void push_command(UndoStack* undo_stack, char* command) {
    if (undo_stack->number_of_elements == undo_stack->array_size) {
        int new_array_size = undo_stack->array_size * 2;
        char** new_array = (char**)malloc(new_array_size*sizeof(char*));

        for (int i = 0; i < undo_stack->number_of_elements; i++) {
            new_array[i] = undo_stack->commands[i];
        }

        undo_stack->array_size = new_array_size;
        free(undo_stack->commands);
        undo_stack->commands = new_array;
        //printf("Resized to %d positions\n", undo_stack->array_size);
    }

    /**
    for (int i = 0; i < undo_stack->number_of_elements; i++) {
        if (!strcmp(undo_stack->commands[i], command))
            return;
    }
    **/

    int number_of_elements = undo_stack->number_of_elements;
    undo_stack->commands[number_of_elements] = (char*)malloc(50*sizeof(char));
    strcpy(undo_stack->commands[number_of_elements], command);
    undo_stack->number_of_elements++;
}


char* pop_command(UndoStack* undo_stack) {
    int last_element = undo_stack->number_of_elements - 1;
    char* last_command = undo_stack->commands[last_element];  //// POSSIBLE MEMORY LEAK

    undo_stack->number_of_elements--;
    return last_command;
}


void free_undo_stack(UndoStack* undo_stack) {
    for (int i = 0; i < undo_stack->number_of_elements; i++) {
        free(undo_stack->commands[i]);
    }

    free(undo_stack->commands);
}
