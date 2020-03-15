#include "tests.h"
#include <stdlib.h>
#include <stdio.h>

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


void test_signal_as_string() {
    Signal signal = create_signal(123, "abc", "def", 456);

    char* signal_string = get_signal_as_string(&signal);

    assert(strcmp(signal_string, "123 abc def 456") == 0);
    free(signal_string);

    printf("Signal as string test passed!\n");
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


void test_repository_search_operation() {
    SignalRepository repository = create_repository();
    add_signal(&repository, 789, "abc", "def", 111);

    Signal signal = search_signal(&repository, 789);
    assert(signal.id == 789);

    printf("Repository search operation test passed!\n");
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
    free_service(&service);
}


void test_service_add_operation() {
    SignalRepository repository = create_repository();
    Service service = create_service(&repository);
    service_add(&service, 123, "abc", "def", 456);
    SignalContainer container = get_signal_container(&repository);

    assert(container.signals[0].id == 123);
    printf("Service add operation test passed!\n");
    free_service(&service);
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
    free_service(&service);
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
    free_service(&service);
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
    free_service(&service);
}


void test_create_undo_stack() {
    UndoStack undo_stack = create_undo_stack();

    assert(undo_stack.number_of_elements == 0);
    assert(undo_stack.array_size == 4);
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

    assert(strcmp(last_command, "4 ddd ddd 123") == 0);
    assert(undo_stack.number_of_elements == 3);
    free_undo_stack(&undo_stack);
    //free(last_command);

    printf("Stack popping test passed!\n");
}


void test_service_split_into_tokens() {
    SignalRepository repository = create_repository();
    Service service = create_service(&repository);

    char* tokens[5];
    char command[] = "add 123 abc def 456";
    service_split_into_tokens(&service, command, tokens);

    assert(strcmp(tokens[0], "add") == 0);
    assert(strcmp(tokens[1], "123") == 0);
    assert(strcmp(tokens[2], "abc") == 0);
    assert(strcmp(tokens[3], "def") == 0);
    assert(strcmp(tokens[4], "456") == 0);

    printf("Service \"split_into_tokens\" operation test passed!\n");
    free_service(&service);
}


void test_service_get_reversed_command_of_add() {
    SignalRepository repository = create_repository();
    Service service = create_service(&repository);

    char* command = "add 123 abc def 456";
	char* correct_reversed_command = "delete 123";
    char* reversed_command = service_get_reversed_command(&service, command);

    assert(strcmp(reversed_command, correct_reversed_command) == 0);

    printf("Service \"get_reversed_command_of_add\" operation test passed!\n");
    free_service(&service);
    free(reversed_command);
}


void test_service_get_reversed_command_of_delete() {
    SignalRepository repository = create_repository();
    Service service = create_service(&repository);
    service_add(&service, 123, "abc", "def", 456);

    char command[] = "delete 123";
    char* reversed_command = service_get_reversed_command(&service, command);
    char correct_reversed_command[] = "add 123 abc def 456";

    assert(strcmp(reversed_command, correct_reversed_command) == 0);

    printf("Service \"get_reversed_command_of_delete\" operation test passed!\n");
    free_service(&service);
    free(reversed_command);
}


void test_service_get_reversed_command_of_update() {
    SignalRepository repository = create_repository();
    Service service = create_service(&repository);
    service_add(&service, 1, "a", "b", 2);

    char command[] = "update 1 z z 5";
    char* reversed_command = service_get_reversed_command(&service, command);

    assert(strcmp(reversed_command, "update 1 a b 2") == 0);

    printf("Service \"get_reversed_command_of_update\" operation test passed!\n");
    free_service(&service);
    free(reversed_command);
}


void test_service_push_last_command_on_stack__command_add() {
    SignalRepository repository = create_repository();
    Service service = create_service(&repository);

    char* command = "add 1 a a 1";

    service_push_last_command_on_stack(&service, command);

    char* reversed_command = pop_command(&service.undo_stack);
    char* actual_command = pop_command(&service.undo_stack);

    assert(strcmp(reversed_command, "delete 1") == 0);
    assert(strcmp(actual_command, "add 1 a a 1") == 0);

    printf("Service \"push_last_command_on_stack__command_add\" operation test passed!\n");
    free_service(&service);
}


void test_service_push_last_command_on_stack__command_delete() {
    SignalRepository repository = create_repository();
    Service service = create_service(&repository);
    service_add(&service, 2, "b", "b", 2);
    char command[] = "delete 2";

    service_push_last_command_on_stack(&service, command);

    char* reversed_command = pop_command(&service.undo_stack);
    char* actual_command = pop_command(&service.undo_stack);

    assert(strcmp(actual_command, "delete 2") == 0);
    assert(strcmp(reversed_command, "add 2 b b 2") == 0);

    printf("Service \"push_last_command_on_stack__command_delete\" operation test passed!\n");

    free_service(&service);
}


void run_all_tests() {
    test_signal_creation_and_getters();
    test_signal_setters();
    test_signal_as_string();
    test_repository_creation();
    test_repository_add_operation();
    test_repository_delete_operation();
    test_repository_update_operation();
    test_repository_search_operation();
    test_service_creation();
    test_service_add_operation();
    test_service_delete_operation();
    test_service_update_operation();
    test_service_get_container_operation();
    test_create_undo_stack();
    test_push_command();
    test_pop_command();
    test_service_split_into_tokens();
    test_service_get_reversed_command_of_add();
    test_service_get_reversed_command_of_delete();
    test_service_get_reversed_command_of_update();
    test_service_push_last_command_on_stack__command_add();
    test_service_push_last_command_on_stack__command_delete();
}
