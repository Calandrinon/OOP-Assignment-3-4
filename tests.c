#include "tests.h"
#include <stdlib.h>

void test_signal_creation_and_getters() {
    Signal signal = create_signal(123, "abc", "def", 456);
    /**
    printf("signal ID: %d\n", get_signal_id(&signal));
    printf("modulated signal: %s\n", get_modulated_signal(&signal));
    printf("signal type: %s\n", get_signal_type(&signal));
    printf("signal priority number: %d\n", get_signal_priority_number(&signal));
    **/
    assert(get_signal_id(&signal) == 123);
    assert(strcmp(get_modulated_signal(&signal), "abc") == 0);
    assert(strcmp(get_signal_type(&signal), "def") == 0);
    assert(get_signal_priority_number(&signal) == 456);

    printf("Signal creation and getters test passed!\n");
}


void test_signal_setters() {
    Signal signal = create_signal(123, "abc", "def", 456);

    set_signal_id(&signal, 100);
    set_modulated_signal(&signal, "ghi");
    set_signal_type(&signal, "jkl");
    set_signal_priority_number(&signal, 200);

    assert(get_signal_id(&signal) == 100);
    assert(strcmp(get_modulated_signal(&signal), "ghi") == 0);
    assert(strcmp(get_signal_type(&signal), "jkl") == 0);
    assert(get_signal_priority_number(&signal) == 200);

    printf("Signal setters test passed!\n");
}


void test_repository_creation() {
    SignalRepository repository = create_repository();
    assert(repository.container.number_of_elements == 0);
    printf("Repository creation test passed!\n");
    free_repository(&repository);
}


void test_repository_add_operation() {
    SignalRepository repository = create_repository();
    add_signal(&repository, 123, "abc", "def", 456);
    assert(repository.container.number_of_elements == 1);
    assert(repository.container.signals[0].id == 123);
    assert(repository.container.signals[0].priority_number == 456);
    assert(strcmp(repository.container.signals[0].modulated_signal, "abc") == 0);
    assert(strcmp(repository.container.signals[0].type, "def") == 0);
    printf("Repository add operation test passed!\n");
    free_repository(&repository);
}


void test_repository_delete_operation() {
    SignalRepository repository = create_repository();
    add_signal(&repository, 123, "abc", "def", 456);
    add_signal(&repository, 789, "abc", "def", 111);
    add_signal(&repository, 222, "abc", "def", 333);
    delete_signal_by_id(&repository, 789);

    int id789_not_deleted = 1;
    for (int i = 0; i < repository.container.number_of_elements && id789_not_deleted; i++) {
        if (repository.container.signals[i].id == 789)
            id789_not_deleted = 0;
    }

    assert(id789_not_deleted == 1);
    assert(repository.container.number_of_elements == 2);
    printf("Repository delete operation test passed!\n");
    free_repository(&repository);
}


void test_repository_update_operation() {
    SignalRepository repository = create_repository();
    add_signal(&repository, 789, "abc", "def", 111);
    update_signal(&repository, 789, "aaa", "bbb", 2);
    SignalContainer container = get_signal_container(&repository);
    int size = container.number_of_elements;


    assert(strcmp(container.signals[size-1].modulated_signal, "aaa") == 0);
    assert(strcmp(container.signals[size-1].type, "bbb") == 0);
    assert(container.signals[size-1].priority_number == 2);
    printf("Repository update operation test passed!\n");
    free_repository(&repository);
}


void test_service_creation() {
    SignalRepository repository = create_repository();
    add_signal(&repository, 123, "abc", "def", 456);
    add_signal(&repository, 789, "abc", "def", 111);
    add_signal(&repository, 222, "abc", "def", 333);
    Service service = create_service(&repository);
    SignalContainer container = get_signal_container(&repository);

    assert(container.signals[1].id == 789);
    printf("Service creation test passed!\n");
    free_repository(&repository);
}


void test_service_add_operation() {
    SignalRepository repository = create_repository();
    Service service = create_service(&repository);
    service_add(&service, 123, "abc", "def", 456);
    SignalContainer container = get_signal_container(&repository);

    assert(container.signals[0].id == 123);
    printf("Service add operation test passed!\n");
    free_repository(&repository);
}


void test_service_delete_operation() {
    SignalRepository repository = create_repository();
    Service service = create_service(&repository);
    service_add(&service, 123, "abc", "def", 456);
    service_add(&service, 789, "abc", "def", 111);
    service_add(&service, 222, "abc", "def", 333);
    service_delete(&service, 789);
    service_delete(&service, 123);


    assert(service.repository->container.number_of_elements == 1);
    printf("Service delete operation test passed!\n");
    free_repository(&repository);
}


void test_service_update_operation() {
    SignalRepository repository = create_repository();
    Service service = create_service(&repository);
    service_add(&service, 123, "abc", "def", 456);
    service_add(&service, 789, "abc", "def", 111);
    service_add(&service, 222, "abc", "def", 333);
    service_update(&service, 789, "aaa", "bbb", 3000);
    SignalContainer container = get_signal_container(&repository);

    assert(strcmp(container.signals[1].modulated_signal, "aaa") == 0);
    assert(strcmp(container.signals[1].type, "bbb") == 0);
    assert(container.signals[1].priority_number == 3000);
    printf("Service update operation test passed!\n");
    free_repository(&repository);
}


void test_service_get_container_operation() {
    SignalRepository repository = create_repository();
    Service service = create_service(&repository);
    service_add(&service, 123, "abc", "def", 456);
    service_add(&service, 789, "abc", "def", 111);
    service_add(&service, 222, "abc", "def", 333);
    SignalContainer container = service_get_container(&service);


    assert(container.number_of_elements == 3);
    assert(container.signals[1].id == 789);
    printf("Service \"get_container\" operation test passed!\n");
    free_repository(&repository);
}


void test_create_undo_stack() {
    UndoStack undo_stack = create_undo_stack();

    assert(undo_stack.number_of_elements == 0);
    assert(undo_stack.array_size == 2);
    free_undo_stack(&undo_stack);

    printf("Undo stack creation test passed!\n");
}


void test_push_command() {
    UndoStack undo_stack = create_undo_stack();

    push_command(&undo_stack, "1 aaa aaa 456");
    push_command(&undo_stack, "2 bbb bbb 123");
    push_command(&undo_stack, "3 ccc ccc 123");
    push_command(&undo_stack, "4 ddd ddd 123");
    push_command(&undo_stack, "5 eee eee 123");
    assert(undo_stack.number_of_elements == 5);
    free_undo_stack(&undo_stack);

    printf("Stack pushing test passed!\n");
}


void test_pop_command() {
    UndoStack undo_stack = create_undo_stack();

    push_command(&undo_stack, "1 aaa aaa 456");
    push_command(&undo_stack, "2 bbb bbb 123");
    push_command(&undo_stack, "3 ccc ccc 123");
    push_command(&undo_stack, "4 ddd ddd 123");
    char* last_command = pop_command(&undo_stack);

    ///printf("last command: %s\n", last_command);
    assert(strcmp(last_command, "4 ddd ddd 123") == 0);
    assert(undo_stack.number_of_elements == 3);
    free_undo_stack(&undo_stack);
    free(last_command);

    printf("Stack popping test passed!\n");
}


void run_all_tests() {
    test_signal_creation_and_getters();
    test_signal_setters();
    test_repository_creation();
    test_repository_add_operation();
    test_repository_delete_operation();
    test_repository_update_operation();
    test_service_creation();
    test_service_add_operation();
    test_service_delete_operation();
    test_service_update_operation();
    test_service_get_container_operation();
    test_create_undo_stack();
    test_push_command();
    test_pop_command();
}
