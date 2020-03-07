#include <stdio.h>
#include <string.h>
#include <stdlib.h>
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


void ui_split_into_tokens(UI* ui, char* tokens[], int* token_index) {
    char* token;
    *token_index = 0;
    token = strtok(ui->last_command, " ");

    while (token != NULL) {
        if ((*token_index) > 0) {
            tokens[*(token_index)-1] = token;
        }

        token = strtok(NULL, " ");
        (*token_index)++;
    }
}


void ui_add(UI* ui) {
    int id, priority_number, token_index;
    char modulated_signal[30], type[30];
    char* tokens[4];

    ui_split_into_tokens(ui, tokens, &token_index);

    if (token_index != 5) {
        printf("Wrong usage. The command \"add\" has 4 parameters: id, modulatedSignal, type, priorityNumber\n");
        return;
    }

    id = atoi(tokens[0]);
    strcpy(modulated_signal, tokens[1]);
    strcpy(type, tokens[2]);
    priority_number = atoi(tokens[3]);

    service_add(ui->service, id, modulated_signal, type, priority_number);
}


void ui_list(UI* ui) {
    SignalContainer container = service_get_container(ui->service);
    char* tokens[2];
    int token_index;

    ui_split_into_tokens(ui, tokens, &token_index);

    if (token_index < 1 || token_index > 2) {
        printf("Wrong usage. The command \"add\" has 4 parameters: id, modulatedSignal, type, priorityNumber\n");
        return;
    }

    for (int i = 0; i < container.size; i++) {
        if (token_index == 2) {
            if (strncmp(container.signals[i].type, tokens[0], strlen(tokens[0])-1) == 0)
                display_signal(&container.signals[i]);
        } else {
            display_signal(&container.signals[i]);
        }
    }
}


void ui_update(UI* ui) {
    int id, new_priority_number, token_index;
    char new_modulated_signal[30], new_type[30];
    char* tokens[4];

    ui_split_into_tokens(ui, tokens, &token_index);

    if (token_index != 5) {
        printf("Wrong usage. The command \"update\" has 4 parameters: id, newModulatedSignal, newType, newPriorityNumber\n");
        return;
    }

    id = atoi(tokens[0]);
    strcpy(new_modulated_signal, tokens[1]);
    strcpy(new_type, tokens[2]);
    new_priority_number = atoi(tokens[3]);

    service_update(ui->service, id, new_modulated_signal, new_type, new_priority_number);
}


void ui_delete(UI* ui) {
    int id, priority_number, token_index;
    char modulated_signal[30], type[30];
    char* tokens[4];

    ui_split_into_tokens(ui, tokens, &token_index);

    if (token_index != 2) {
        printf("Wrong usage. The command \"delete\" has 1 parameter: id\n");
        return;
    }

    id = atoi(tokens[0]);

    service_delete(ui->service, id);
}


void run(UI* ui) {
    char* commands[] = {"exit", "add", "list", "update", "delete"};
    void (*command_functions[])(UI*) = {ui_exit, ui_add, ui_list, ui_update, ui_delete};
    char command[40];
    int number_of_commands = sizeof(commands)/sizeof(commands[0]);

    while (ui->running) {
        printf(">>");
        fgets(command, 40, stdin);
        strcpy(ui->last_command, command);
        int found = 0;
        char* command_name = NULL;

        //obtaining the first token of the command(the command name)
        command_name = strtok(command,  " ");

        for (int i = 0; i < number_of_commands && !found; i++) {
            if (strncmp(command, commands[i], strlen(commands[i])) == 0) {
                found = 1;
                command_functions[i](ui);
            }
        }

        if (!found)
            printf("The command doesn't exist!\n");
    }
}
