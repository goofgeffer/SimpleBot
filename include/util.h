// util.h
#ifndef UTIL_H
#define UTIL_H

#define VERSION "v0.1"

#include <stddef.h> // For size_t

#include "chat.h"

const char *lookup(const char *key, const KeyValuePair *pairs, size_t size);
int is_empty_or_whitespace(const char *string);
int read_line(char *buffer, size_t size);
int is_target_punct(int c);

void print_learn_help(void);
void print_chat_help(void);
void print_command_help(void);

#endif // UTIL_H