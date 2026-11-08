#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "main.h"
#include "terminal.h"
#include "util.h"
#include "chat.h"
#include "learn.h"

// Main function, self-explanatory
int main(void) {
	// Initizalize the terminal so you don't have to call it again
	init_terminal();
	clear_screen();

	printf("SIMPLEBOT COMMAND INTERFACE\n");
	// Buffer for command 
	// What does buffer even mean its thrown around so much
	char command[255];

	// Main loop; runs forever until break keyword			
	for (;;) {
		// Prints the input sign
		printf("> ");
		
		int result = read_line(command, sizeof(command));
		if (result == 0) {
			return 1;
		}
		if (result == -1) {
			printf("Input too long\n");
			continue;
		}
		
		for (int i = 0; command[i]; i++) {
			command[i] = tolower((unsigned char)command[i]); // Convert the input to lowercase for easier comparison
		}
		
		// Did not use a switch statement for the quit commands because i'd have to use break to end the for loop,
		// which is used in switch statements to prevent fall-through
		if (strcmp(command, "q") == 0 || strcmp(command, "quit") == 0 || strcmp(command, "exit") == 0 || strcmp(command, "end") == 0) {
			clear_screen();
			break;
		}
		
		if (strcmp(command, "h") == 0 || strcmp(command, "help") == 0) {
			print_command_help();
		} else if (strcmp(command, "v") == 0 || strcmp(command, "version") == 0) {
		    printf("SimpleBot %s\n", VERSION);
		} else if (strcmp(command, "c") == 0 || strcmp(command, "clear") == 0) {
			clear_screen();
		} else if (strcmp(command, "l") == 0 || strcmp(command, "learn") == 0) {
			int learn_return = run_learning_engine();
			if (learn_return != 0) {
				printf("Error running learning engine\n");
				return 1;
			}
		} else if (strcmp(command, "ch") == 0 || strcmp(command, "chat") == 0) {
			int chat_return = run_chat_engine();
			if (chat_return != 0) {
				printf("Error running chat engine\n");
				return 1;
			}
		} else {
			if (!is_empty_or_whitespace(command)) {
				printf("Unknown command. Type h for help.\n");
			}
		}
	}
	return 0;
}