#include <stdio.h>
#include "signal.h"

void test_signal_creation() {
    Signal signal = create_signal(123, "abc", "def", 456);
    printf("signal ID: %d\n", get_signal_id(&signal));
    printf("modulated signal: %s\n", get_modulated_signal(&signal));
    printf("signal type: %s\n", get_signal_type(&signal));
    printf("signal priority number: %d\n", get_signal_priority_number(&signal));
}

int main() {
    //SignalRepository repository = create_repository();
    //SignalService service = create_service(&repository);
    //UI ui = create_ui(&service);
    //ui.run();
    test_signal_creation();
    return 0;
}
