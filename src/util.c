#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "util.h"

// Dedicated lookup function for the chat interface, O(n) time complexity, but the list is small so it doesn't matter
const char *lookup(const char *key, const KeyValuePair *pairs, size_t size) {
	for (size_t i = 0; i < size; i++) {
		if (strcmp(key, pairs[i].key) == 0) {
			return pairs[i].value;
		}
	}
	return NULL; // Return NULL if the key is not found
}

int is_empty_or_whitespace(const char *string) {
	while (*string != '\0') {
		if (!isspace((unsigned char)*string)) {
			return 0; // Not empty or whitespace
		}
		string++;
	}
	return 1; // Empty or whitespace
}

// Reads a line into buffer. Returns 1 on success, 0 on failure and -1 if line was too long, so different from main-style int return
int read_line(char *buffer, size_t size) {
	if (fgets(buffer, size, stdin) == NULL) {
		return 0;
    }

    if (strchr(buffer, '\n') == NULL) {
    	int character;
    	while ((character = getchar()) != '\n' && character != EOF) { 
    		// Discard
    	}
    	return -1;
    }

    buffer[strcspn(buffer, "\n")] = '\0'; // Removes the damn trailing newline
    return 1;
}

void print_learn_help(void) {
	// Prints the options for the user to choose from
	printf("Options:\n");
	printf("Enter a for: ARITHMETIC\n");
	printf("Enter b for: SHAPES\n");
	printf("Enter c for: PEMDAS\n");
	printf("Enter d for: ELEMENTS OF PERIODIC TABLE\n");
	printf("Enter e for: SCIENTIFIC METHOD\n");
	printf("Enter f for: ATOMS\n");
	printf("Enter help to see the options again\n");
	printf("Enter quit/end/exit to exit the learning interface\n");
}

void print_chat_help(void) {
	printf("Commands:\n");
	printf("quit/end/exit, Ends the chat interface\n");
	printf("help, Shows this help message\n");
	printf("vocab, Shows a list of words the chatbot can understand\n");
}

void print_command_help(void){
	// Just prints the name of app, version, and a list of commands.
	printf("SimpleBot %s\n", VERSION);
	printf("Commands:\n");
	printf("q/quit OR exit OR end, Ends the command interface\n");
	printf("h/help, Help about the commands\n");
	printf("v/version, Current version\n");
	printf("c/clear, Clears the screen\n");
	printf("l/learn, Enters the learning engine interface, lets you choose from a list of subjects and you get a rough overview of each\n");
	printf("ch/chat, Enters the chat interface, where you can ask questions and get answers\n");
}