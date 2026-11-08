#include "terminal.h"
#include <stdio.h>

#ifdef _WIN32
#include <windows.h>

#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
// On Windows, this constant is not defined in older versions of the Windows SDK, so we define it here for compatibility.
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#endif
#endif

// I hate Windows, this is historical baggage. Why doesn't cmd.exe just support ANSI escape codes like every other terminal in existence.
void init_terminal(void) {
#ifdef _WIN32
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD mode;
	if ((GetConsoleMode(hOut, &mode))) {
		SetConsoleMode(hOut, mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING);
	}
#endif
}

void clear_screen(void) {
	printf("\033[2J\033[H"); // ANSI escape code to clear the screen
	fflush(stdout); // Ensure the output is flushed to the terminal
}