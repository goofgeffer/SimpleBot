#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "data.h"

// Dedicated lookup function for the chat interface, O(n) time complexity, but the list is small so it doesn't matter
const char *lookup(const char *key, const KeyValuePair *pairs, size_t size) {
	for (size_t i = 0; i < size; i++) {
		if (strcmp(key, pairs[i].key) == 0) {
			return pairs[i].value;
		}
	}
	return NULL; // Return NULL if the key is not found
}

int print_learn_help() {
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
	return 0;
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

// Main function, self-explanatory
int main(void) {
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
			break;
		}
		
		if (strcmp(command, "h") == 0 || strcmp(command, "help") == 0) {
			// Just prints the name of app, version, and a list of commands.
		    printf("SimpleBot %s\n", VERSION);
			printf("Commands:\n");
		    printf("q/quit OR exit OR end, Ends the command interface\n");
		    printf("h/help, Help about the commands\n");
		    printf("v/version, Current version\n");
			printf("c/clear, Clears the screen\n");
		    printf("l/learn, Enters the learning engine interface, lets you choose from a list of subjects and you get a rough overview of each\n");
			printf("ch/chat, Enters the chat interface, where you can ask questions and get answers\n");
		} else if (strcmp(command, "v") == 0 || strcmp(command, "version") == 0) {
		    printf("SimpleBot %s\n", VERSION);
		} else if (strcmp(command, "c") == 0 || strcmp(command, "clear") == 0) {
			CLEAR_SCREEN();
		} else if (strcmp(command, "l") == 0 || strcmp(command, "learn") == 0) {
			printf("SIMPLEBOT LEARNING ENGINE\n");
			printf("Quick overviews of topics, with examples\n");

			print_learn_help();
			
			char line[255];
			size_t limit = sizeof(topics) / sizeof(topics[0]) - 1; // Dynamic limit of topics, not hardcoded so I dont have to update this everytime a new topic comes by. Subtract by 1 so it's the index limit not number of topics
			
			for (;;) {
				printf("Choose a letter: ");

				// learn_result so I dont get mixed up with the earlier result variable, which is used for the main command input
				int learn_result = read_line(line, sizeof(line));
				if (learn_result == 0) {
					return 1;
				}
				if (learn_result == -1) {
					printf("Input too long\n");
					continue;
				}	

				for (int i = 0; line[i]; i++) {
					line[i] = tolower((unsigned char)line[i]); // Convert the input to lowercase for easier comparison
				}

				// These if statements only work because we test for them before falling through to the letter logic, so always put these like word checks above the letter logic
				if (strcmp(line, "quit") == 0 || strcmp(line, "end") == 0 || strcmp(line, "exit") == 0) {
					break;	
				}
				
				if (strcmp(line, "help") == 0) {	
					print_learn_help();
					continue;
				}

				char chosen_character = line[0];

				if (isalpha((unsigned char)chosen_character)) {
					size_t index = tolower((unsigned char)chosen_character) - 'a';
					if (index > limit) {
						printf("Choose a letter from the list\n");
						continue;
					}
					printf("%s", topics[index]); // Print a rough definition of the topic
					
				} else {
					printf("No letter chosen. Enter help to see letters\n");
					continue;
				}
			}
		} else if (strcmp(command, "ch") == 0 || strcmp(command, "chat") == 0) {
			char input[255];

			const char *delimiters = " \t\n.!?,"; // Delimiters for tokenizing the input

			printf("SIMPLEBOT CHAT INTERFACE\n");

			for (;;) {
				int chat_result = read_line(input, sizeof(input));
				if (chat_result == 0) {
					return 1;
				}
				if (chat_result == -1) {
					printf("Input too long\n");
					continue;
				}

				for (int i = 0; input[i]; i++) {
					input[i] = tolower((unsigned char)input[i]); // Convert the input to lowercase for easier comparison
				}

				if (strcmp(input, "quit") == 0 || strcmp(input, "end") == 0 || strcmp(input, "exit") == 0) {
					break;	
				}

				// Parse the input into words and look it up in a list of key-value structs.

				// We are praying the user does not input a quotation mark, because strtok will break the input into two tokens and we will not be able to find the key in the list. 
				// I could use regex to parse the input but that would be overkill for this project.
				// Plus, theres no 2-word keys in the pair list (as of now) so it should be fine.
				char *token = strtok(input, delimiters);
				char answer_buffer[255] = ""; // Buffer to store the answer from the chatbot

    			while (token != NULL) {
					const char *value = lookup(token, chat_pairs, sizeof(chat_pairs) / sizeof(chat_pairs[0]));
					if (value != NULL) {
						strcat(answer_buffer, value);
						strcat(answer_buffer, " "); // Add a space after each word
					} else {
						strcat(answer_buffer, "not sure "); // If the word is not found, add "not sure" to the answer
					}
					token = strtok(NULL, delimiters);
    			}

				printf("%s\n", answer_buffer);
			}
		} else {
			printf("Unknown command. Type h for help.\n");
		}
	}
	return 0;
}