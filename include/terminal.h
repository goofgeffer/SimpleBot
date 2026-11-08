// terminal.h
#ifndef TERMINAL_H
#define TERMINAL_H

// cmd.exe functions to enable ANSI escape codes
// Necessary because Windows cmd.exe does not support ANSI escape codes by default, and we have to enable it manually.
void init_terminal(void);
void clear_screen(void);

#endif // TERMINAL_H