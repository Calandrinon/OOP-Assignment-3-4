#ifndef __TESTS_H__
#define __TESTS_H__
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "signal.h"
#include "repository.h"
#include "service.h"
#include "ui.h"

void test_signal_creation_and_getters();
void test_signal_setters();
void test_repository_creation();
void test_repository_add_operation();
void test_repository_delete_operation();
void test_repository_update_operation();
void test_service_creation();
void test_service_add_operation();
void test_service_delete_operation();
void test_service_update_operation();
void test_service_get_container_operation();
void run_all_tests();

#endif
