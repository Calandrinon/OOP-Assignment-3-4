#include "service.h"

Service create_service(SignalRepository* repository) {
    Service service;
    service.repository = repository;
    return service;
}


void service_add(Service* service, int id, char modulated_signal[], char type[], int priority_number) {
    add_signal(service->repository, id, modulated_signal, type, priority_number);
}


void service_delete(Service* service, int id) {
    SignalRepository new_repository = *(service->repository);
    delete_signal_by_id(&new_repository, id);
    *(service->repository) = new_repository;
}


void service_update(Service *service, int id, char new_modulated_signal[], char new_type[], int new_priority_number) {
    SignalRepository new_repository = *(service->repository);
    update_signal(&new_repository, id, new_modulated_signal, new_type, new_priority_number);
    *(service->repository) = new_repository;
}


SignalContainer service_get_container(Service* service) {
	SignalRepository repository = *(service->repository);
	SignalContainer container = get_signal_container(&repository);
	return container;
}
