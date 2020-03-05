#include "repository.h"
#include <stdio.h>

SignalRepository create_repository() {
    SignalRepository repository;
    repository.container.size = 0;
    return repository;
}


void add_signal(SignalRepository *repository, int id, char modulated_signal[], char type[], int priority_number) {
    for (int i = 0; i < repository->container.size; i++) {
        if (repository->container.signals[i].id == id) {
            printf("No!\n");
            return;
        }
    }

    int size = repository->container.size;
    repository->container.signals[size] = create_signal(id, modulated_signal, type, priority_number);
    repository->container.size++;
}


void delete_signal_by_id(SignalRepository *repository, int signal_id) {
    int id_found = 0;

    for (int i = 0; i < repository->container.size; i++) {
        if (repository->container.signals[i].id == signal_id)
            id_found = 1;

        if (id_found)
            repository->container.signals[i] = repository->container.signals[i+1];
    }

    if (id_found)
        repository->container.size--;
    else
        printf("No!\n");
}


void update_signal(SignalRepository *repository, int id, char new_modulated_signal[], char new_type[], int new_priority_number) {
    for (int i = 0; i < repository->container.size; i++) {
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
