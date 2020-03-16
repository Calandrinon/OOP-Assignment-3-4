#include "repository.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

SignalRepository create_repository() {
    /**
        Creates a repository and initializes all the members of the struct SignalRepository.
        Returns the created repository.

        Output:
            - a struct of type Repository
    **/

    SignalRepository repository;
    repository.container.number_of_elements = 0;
    repository.container.array_size = 2;
    repository.container.signals = (Signal*)malloc(repository.container.array_size*sizeof(Signal));

    return repository;
}


void add_signal(SignalRepository *repository, int id, char modulated_signal[], char type[], int priority_number) {
    /**
        Adds a signal with the given parameters to the repository.

        Input:
            - repository: a pointer to a Repository struct
            - id: int
            - modulated_signal: string
            - type: string
            - priority_number: int
    **/

    if (repository->container.number_of_elements == repository->container.array_size) {
        int new_signals_array_size = repository->container.array_size * 2;
        Signal* new_signals_array = (Signal*)malloc(new_signals_array_size*sizeof(Signal));

        for (int i = 0; i < repository->container.number_of_elements; i++) {
            new_signals_array[i] = repository->container.signals[i];
        }

        repository->container.array_size = new_signals_array_size;
        free(repository->container.signals);
        repository->container.signals = new_signals_array;
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
    /**
        Deletes a signal with the given id from the repository.

        Input:
            - repository: a pointer to a Repository struct
            - id: int
    **/

    int id_found = 0;

    for (int i = 0; i < repository->container.number_of_elements; i++) {
        if (repository->container.signals[i].id == signal_id)
            id_found = 1;

        if (id_found && i + 1 < repository->container.number_of_elements)
            repository->container.signals[i] = repository->container.signals[i+1];
    }

    if (id_found)
        repository->container.number_of_elements--;
    else
        printf("No!\n"); // There's no exceptions in C.
                         // Maybe I should have bothered to return a boolean value in this case
                         // instead of printing from the repository.
}


void update_signal(SignalRepository *repository, int id, char new_modulated_signal[], char new_type[], int new_priority_number) {
    /**
        Updates a signal with the given parameters from the repository.

        Input:
            - repository: a pointer to a Repository struct
            - id: int
            - new_modulated_signal: string
            - new_type: string
            - new_priority_number: int
    **/

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
    /**
        Searches a signal with the given signal_id and returns it
        from the repository in case it exists. Otherwise, it will return
        a dummy Signal struct with all values set to -1.

        Input:
            - repository: a pointer to a Repository struct
            - signal_id: int

        Output:
            - signal: the searched signal with id "signal_id"
            OR:
            - a signal with the values set to -1, in case a signal with id
            "signal_id" is not found
    **/

    for (int i = 0; i < repository->container.number_of_elements; i++) {
        if (repository->container.signals[i].id == signal_id)
            return repository->container.signals[i];
    }

    Signal signal = create_signal(-1, "-1", "-1", -1);
    return signal;
}


SignalContainer get_signal_container(const SignalRepository *repository) {
    /**
        Gets the container associated with the repository pointed to by
        "const SignalRepository* repository".

        Input:
            - repository: a pointer to a Repository struct

        Output:
            - container: the container associated with the repository
    **/

    return repository->container;
}


void free_repository(SignalRepository* repository) {
    /**
        Frees the dynamically allocated resources used by the struct pointed to by SignalRepository* repository.

        Input:
            - repository: a pointer to the SignalRepository struct
    **/

    free(repository->container.signals);
}

UndoStack create_undo_stack() {
    /**
        Creates a stack and initializes all the members of the struct UndoStack.
        Returns the created repository.

        Output:
            - a struct of type UndoStack
    **/

    UndoStack undo_stack;
    undo_stack.number_of_elements = 0;
    undo_stack.array_size = 4;
    undo_stack.commands = (char**)malloc(undo_stack.array_size*sizeof(char*));

    for (int i = 0; i < undo_stack.array_size; i++) {
        undo_stack.commands[i] = (char*)malloc(35*sizeof(char));
    }

    return undo_stack;
}


void push_command(UndoStack* undo_stack, char* command) {
    /**
        Pushes the command "command" onto the stack pointed to by "undo_stack"

        Input:
            - undo_stack: a pointer to an UndoStack struct
            - command: string
    **/

    if (undo_stack->number_of_elements == undo_stack->array_size) {
        int new_array_size = undo_stack->array_size * 2;
        char** new_array = (char**)malloc(new_array_size*sizeof(char*));

        for (int i = 0; i < undo_stack->number_of_elements; i++) {
            new_array[i] = undo_stack->commands[i];
        }

        for (int i = undo_stack->array_size; i < new_array_size; i++) {
            new_array[i] = (char*)malloc(35*sizeof(char));
        }

        undo_stack->array_size = new_array_size;
        free(undo_stack->commands);
        undo_stack->commands = new_array;
        //printf("Resized to %d positions\n", undo_stack->array_size);
    }

    int number_of_elements = undo_stack->number_of_elements;

    strcpy(undo_stack->commands[number_of_elements], command);

    undo_stack->number_of_elements++;
}


char* pop_command(UndoStack* undo_stack) {
    /**
        Pops the command "command" from the stack pointed to by "undo_stack"

        Input:
            - undo_stack: a pointer to an UndoStack struct

        Output:
            - last_command: the element from the top of the command stack
    **/

    int last_element = undo_stack->number_of_elements - 1;
    char* last_command = undo_stack->commands[last_element];  //// POSSIBLE MEMORY LEAK

    undo_stack->number_of_elements--;
    return last_command;
}


void free_undo_stack(UndoStack* undo_stack) {
    /**
        Frees the dynamically allocated resources used by the struct pointed to by UndoStack* undo_stack.

        Input:
            - undo_stack: a pointer to an UndoStack struct
    **/

    for (int i = 0; i < undo_stack->array_size; i++) {
        free(undo_stack->commands[i]);
    }

    free(undo_stack->commands);
}
