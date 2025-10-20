#pragma once

#define ERROR(msg) error_handler(__FILE__, __func__, __LINE__, msg)

void error_handler(const char *file, const char *func, const int line,
                   char *msg);