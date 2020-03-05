#ifndef __UI_H__
#define __UI_H__
#include "service.h"

typedef struct {
    Service* service;
    int running;
} UI;

UI create_ui(Service* service);
void ui_exit(UI* ui);
void run(UI* ui);

#endif
