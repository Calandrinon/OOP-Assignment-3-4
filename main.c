#include <stdio.h>
#include "tests.h"

int main() {
	run_all_tests();

    SignalRepository repository = create_repository();
    Service service = create_service(&repository);
    UI ui = create_ui(&service);
    run(&ui);
    return 0;
}
