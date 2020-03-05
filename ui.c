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
    char* commands[] = {"exit\0"};
    void (*command_functions[])(UI*) = {ui_exit};
    char command[40];

    int number_of_commands = sizeof(commands)/sizeof(commands[0]);
    printf("%d\n", number_of_commands);

    while (ui->running) {
        fgets(command, 40, stdin);
        int found = 0;

        for (int i = 0; i < number_of_commands && !found; i++) {
            if (strncmp(command, commands[i], strlen(commands[i])) == 0) {
                found = 1;
                command_functions[i](ui);
            }
        }
    }
}
