#include "repository.h"
#include <stdio.h>
#include <stdlib.h>

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


SignalContainer get_signal_container(const SignalRepository *repository) {
    return repository->container;
}


void free_repository(SignalRepository* repository) {
    free(repository->container.signals);
}
