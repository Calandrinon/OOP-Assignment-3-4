#include "service.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

Service create_service(SignalRepository* repository) {
    /**
        Creates a service and initializes all the members of the struct Service.
        Returns the created service.

        Input:
            - service: a pointer to the repository associated with the service

        Output:
            - a struct of type Service
    **/

    Service service;
    service.repository = repository;
    service.undo_stack = create_undo_stack();
    service.redo_stack = create_undo_stack();
    return service;
}


void service_add(Service* service, int id, char modulated_signal[], char type[], int priority_number) {
    /**
        Adds a signal with the given parameters into the repository with the
        function "add_signal".

        Input:
            - service: a pointer to the Service struct
            - id: int
            - modulated_signal: string
            - type: string
            - priority_number: int
    **/

    add_signal(service->repository, id, modulated_signal, type, priority_number);
}


void service_delete(Service* service, int id) {
    /**
        Deletes a signal with the id "id" from the repository with the
        function "delete_signal_by_id".

        Input:
            - service: a pointer to the Service struct
            - id: int
    **/

    SignalRepository new_repository = *(service->repository);
    delete_signal_by_id(&new_repository, id);
    *(service->repository) = new_repository;
}


void service_update(Service *service, int id, char new_modulated_signal[], char new_type[], int new_priority_number) {
    /**
        Updates a signal with the given id and new parameters into the repository with the
        function "update_signal".

        Input:
            - service: a pointer to the Service struct
            - id: int
            - new_modulated_signal: string
            - new_type: string
            - new_priority_number: int
    **/

    SignalRepository new_repository = *(service->repository);
    update_signal(&new_repository, id, new_modulated_signal, new_type, new_priority_number);
    *(service->repository) = new_repository;
}


SignalContainer service_get_container(Service* service) {
    /**
        Gets the container from the repository.

        Input:
            - service: a pointer to the Service struct

        Output:
            - container: the desired container
    **/

	SignalRepository repository = *(service->repository);
	SignalContainer container = get_signal_container(&repository);
	return container;
}


void free_service(Service* service) {
    /**
        Frees the dynamically allocated resources used by the struct pointed to by Service* service.

        Input:
            - service: a pointer to the Service struct
    **/

    free_repository(service->repository);
    free_undo_stack(&service->undo_stack);
    free_undo_stack(&service->redo_stack);
}


void service_split_into_tokens(Service* service, char* command, char* tokens[]) {
    /**
        Splits a command into tokens.

        Input:
            - service: a pointer to the Service struct
            - command: string

        Output:
            - tokens: the tokens obtained from the command
    **/

    int token_index = 0;
    char* token = strtok(command, " ");

    while (token != NULL) {
        tokens[token_index] = token;
        token = strtok(NULL, " ");
        token_index++;
    }
}


char* service_get_reversed_command(Service* service, char* command) {
    /**
        Returns the reverse of a command.
        Example: for "add 1 a a 1", it returns delete 1

        Input:
            - service: a pointer to the Service struct
            - command: string

        Output:
            - reversed: the reversed command
    **/

    char* tokens[5];
    char command_string[50];
    strcpy(command_string, command);
    service_split_into_tokens(service, command_string, tokens);


    if (strcmp(tokens[0], "add") == 0) {
        char* reversed = (char*)malloc(sizeof(char)*35);
        strcpy(reversed, "delete ");

        return strcat(reversed, tokens[1]);
    } else if (strcmp(tokens[0], "delete") == 0) {
        char* reversed = (char*)malloc(sizeof(char)*35);
        strcpy(reversed, "add ");
        int id = atoi(tokens[1]);

        Signal signal = search_signal(service->repository, id);

        if (signal.id == -1) {
            free(reversed);
            return NULL;
        }

        char* signal_as_string = get_signal_as_string(&signal);
        reversed = strcat(reversed, signal_as_string);
        free(signal_as_string);

        return reversed;
    } else if (strcmp(tokens[0], "update") == 0) {
        char* reversed = (char*)malloc(sizeof(char)*35);
        strcpy(reversed, "update ");

        Signal signal = search_signal(service->repository, atoi(tokens[1]));
        if (signal.id == -1) {
            free(reversed);
            return NULL;
        }

        char* signal_as_string = get_signal_as_string(&signal);
        reversed = strcat(reversed, signal_as_string);
        free(signal_as_string);

        return reversed;
    }

    return NULL;
}


void service_push_last_command_on_stack(Service* service, char* last_command) {
    /**
        Pushes the last command that has been given on a stack of previously
        executed commands.
        Used for the undo feature.

        Input:
            - service: a pointer to the Service struct
            - command: string
    **/
    char* reversed_command = service_get_reversed_command(service, last_command);

    if (reversed_command == NULL)
        return;

    push_command(&service->undo_stack, last_command);
    push_command(&service->undo_stack, reversed_command);

    free(reversed_command);
}


void service_undo(Service* service) {
    /**
        Undoes the last executed command.

        Input:
            - service: a pointer to the Service struct
    **/

    if (service->undo_stack.number_of_elements == 0)
        /// Validates the size of the stack before undoing,
        /// otherwise the program would issue a segmentation fault in the
        /// case of an empty stack.
        return;

    char* reversed_command = pop_command(&service->undo_stack);
    char* actual_command = pop_command(&service->undo_stack);
    char* tokens[5];

    service_split_into_tokens(service, strdup(reversed_command), tokens);

    if (strcmp(tokens[0], "add") == 0) {
        service_add(service, atoi(tokens[1]), tokens[2], tokens[3], atoi(tokens[4]));
    } else if (strcmp(tokens[0], "delete") == 0) {
        service_delete(service, atoi(tokens[1]));
    } else if (strcmp(tokens[0], "update") == 0) {
        service_update(service, atoi(tokens[1]), tokens[2], tokens[3], atoi(tokens[4]));
    }

    push_command(&service->redo_stack, reversed_command);
    push_command(&service->redo_stack, actual_command);
}


void service_redo(Service* service) {
    /**
        Redoes the last undone command.

        Input:
            - service: a pointer to the Service struct
    **/

    if (service->redo_stack.number_of_elements == 0)
        return;

    char* actual_command = pop_command(&service->redo_stack);
    char* reversed_command = pop_command(&service->redo_stack);
    char* tokens[5];

    service_split_into_tokens(service, strdup(actual_command), tokens);

    if (strcmp(tokens[0], "add") == 0) {
        service_add(service, atoi(tokens[1]), tokens[2], tokens[3], atoi(tokens[4]));
    } else if (strcmp(tokens[0], "delete") == 0) {
        service_delete(service, atoi(tokens[1]));
    } else if (strcmp(tokens[0], "update") == 0) {
        service_update(service, atoi(tokens[1]), tokens[2], tokens[3], atoi(tokens[4]));
    }

    push_command(&service->undo_stack, actual_command);
    push_command(&service->undo_stack, reversed_command);
}
