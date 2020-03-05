#include <stdio.h>
#include <string.h>
#include "ui.h"
#define true 1
#define false 0

UI create_ui(Service* service) {
    UI ui;
    ui.running = true;
    ui.service = service;
    return ui;
}


void ui_exit(UI* ui) {
    ui->running = false;
}


void run(UI* ui) {
    char* commands[] = {"exit"};
    void (*command_functions[])() = {ui_exit};
    char command[40];

    while (ui->running) {
        fgets(command, 40, stdin);

        if (strncmp(command, "exit", 4) == 0)
            ui_exit(ui);
    }
}
