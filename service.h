#ifndef __SERVICE_H__
#define __SERVICE_H__
#include "repository.h"

typedef struct {
    SignalRepository* repository;
    UndoStack undo_stack;
} Service;

Service create_service(SignalRepository* repository);
void service_add(Service* service, int id, char modulated_signal[], char type[], int priority_number);
void service_delete(Service* service, int id);
void service_update(Service* service, int id, char modulated_signal[], char type[], int priority_number);
SignalContainer service_get_container(Service* service);
void service_push_last_command_on_stack(Service* service, char* last_command);
void service_split_into_tokens(Service* service, char* command, char* tokens[]);
char* service_get_reversed_command(Service* service, char* command);
void service_undo(Service* service);
void free_service(Service* service);

#endif
