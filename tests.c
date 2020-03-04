#include "tests.h"

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
    assert(repository.container.size == 0);
    printf("Repository creation test passed!\n");
}


void test_repository_add_operation() {
    SignalRepository repository = create_repository();
    add_signal(&repository, 123, "abc", "def", 456);
    assert(repository.container.size == 1);
    assert(repository.container.signals[0].id == 123);
    assert(repository.container.signals[0].priority_number == 456);
    assert(strcmp(repository.container.signals[0].modulated_signal, "abc") == 0);
    assert(strcmp(repository.container.signals[0].type, "def") == 0);
    printf("Repository add operation test passed!\n");
}


void test_repository_delete_operation() {
    SignalRepository repository = create_repository();
    add_signal(&repository, 123, "abc", "def", 456);
    add_signal(&repository, 789, "abc", "def", 111);
    add_signal(&repository, 222, "abc", "def", 333);
    delete_signal_by_id(&repository, 789);

    int id789_not_deleted = 0;
    for (int i = 0; i < repository.container.size; i++) {
        if (repository.container.signals[i].id == 789)
            id789_not_deleted = 1;
    }

    assert(id789_not_deleted == 0);
    assert(repository.container.size == 2);
    printf("Repository delete operation test passed!\n");
}


void test_repository_update_operation() {
    SignalRepository repository = create_repository();
    add_signal(&repository, 789, "abc", "def", 111);
    update_signal(&repository, 789, "aaa", "bbb", 2);
    int size = repository.container.size;

    assert(strcmp(repository.container.signals[size-1].modulated_signal, "aaa") == 0);
    assert(strcmp(repository.container.signals[size-1].type, "bbb") == 0);
    assert(repository.container.signals[size-1].priority_number == 2);
    printf("Repository update operation test passed!\n");
}


void run_all_tests() {
    test_signal_creation_and_getters();
    test_signal_setters();
    test_repository_creation();
    test_repository_add_operation();
    test_repository_delete_operation();
    test_repository_update_operation();
}
