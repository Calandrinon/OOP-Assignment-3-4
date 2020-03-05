#ifndef __SERVICE_H__
#define __SERVICE_H__
#include "repository.h"

typedef struct {
    SignalRepository* repository;
} Service;

Service create_service(SignalRepository* repository);
void service_add(Service* service, int id, char modulated_signal[], char type[], int priority_number);
void service_delete(Service* service, int id);
void service_update(Service* service, int id, char modulated_signal[], char type[], int priority_number);
SignalContainer service_get_container(Service* service);

#endif
