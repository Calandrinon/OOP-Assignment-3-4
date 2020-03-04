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


void run_all_tests() {
    test_signal_creation_and_getters();
    test_signal_setters();
}
