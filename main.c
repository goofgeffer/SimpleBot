#include <stdio.h>
#include <ctype.h>
#include <string.h>

int print_learn_help(){
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
	printf("SIMPLEBOT CHAT INTERFACE\n");
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
		    printf("SimpleBot v0.1\n");
			printf("Commands:\n");
		    printf("q/quit OR exit OR end, Ends the chat interface\n");
		    printf("h/help, Help about the commands\n");
		    printf("v/version, Current version\n");
		    printf("l/learn, Enters the learning engine interface, lets you choose from a list of subjects and you get a rough overview of each\n");
		} else if (strcmp(command, "v") == 0 || strcmp(command, "version") == 0) {
		    printf("SimpleBot v0.1\n");
		} else if (strcmp(command, "l") == 0 || strcmp(command, "learn") == 0){
			printf("SIMPLEBOT LEARNING ENGINE\n");
			printf("Quick overviews of topics, with examples\n");

			print_learn_help();
			
			char line[255];

 			// List of topics, mostly sourced from Wikipedia
			const char *topics[] = {
				"Arithmetic is a branch of mathematics that deals with operations like addition, subtraction, multiplication, and division. "
				"Arithmetic is very important in day to day life. "
				"Here are 2 examples: 9 + 9 = 18, 5 * 5 = 25\n",
				
				"Shapes are a representation of an object's external boundary or outline. "
				"Simple shapes typically make up our life, such as a square TV or a rectangle. "
				"A few examples of shapes would be a square (4 corners, 4 equal length sides), a triangle (3 corners, 3 sides), and a rectangle (4 corners, 2 pairs of equal length sides but the pairs "
				"are different lengths)\n",

				"PEMDAS is the order of operations used to solve math problems with more than one operation. "
				"It stands for Parentheses, Exponents, Multiplication, Division, Addition, and Subtraction. "
				"Multiplication and division share the same level and are done left to right, and so do addition and subtraction. "
				"Here are 2 examples: 2 + 3 * 4 = 14 (multiply first), (2 + 3) * 4 = 20 (parentheses first)\n",

				"The periodic table is a chart that organizes all known elements by their atomic number, which is how many protons are in that atom. "
				"Elements in the same column have similar properties, and each element has a one or two letter symbol. "
				"Some examples of elements on the table would be hydrogen (H, atomic number 1), carbon (C, atomic number 6), and oxygen (O, atomic number 8)\n",

			    "The scientific method is a step by step process scientists use to investigate questions and test ideas. "
				"The basic steps are: ask a question, do research, form a hypothesis, test it with an experiment, analyze the results, and share the conclusion. "
				"For example, you could question if a sunflower grows faster with more light, do research about it, form a hypothesis, test it with different levels of light, and share the conclusion\n",
				
				"Atoms are building blocks that all matter is made of. "
			    "An atom has a nucleus in the center made of protons (positive charge) and neutrons (no charge), with electrons (negative charge) moving around the outside. "
			    "3 examples of atoms would be a hydrogen atom (1 proton, 1 electron), a helium atom (2 protons, 2 neutrons, 2 electrons), and a carbon atom (6 protons, 6 neutrons, 6 electrons)\n"
			};

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
				
				if (strcmp(line, "help") == 0){	
					print_learn_help();
					continue;
				}

				char chosen_character = line[0];

				if (isalpha((unsigned char)chosen_character)) {
					size_t index = tolower((unsigned char)chosen_character) - 'a';
					if (index > limit){
						printf("Choose a letter from the list\n");
						continue;
					}
					printf("%s", topics[index]); // Print a rough definition of the topic
					
				} else {
					printf("No letter chosen. Enter help to see letters\n");
					continue;
				}
			}
		} else {
			printf("Unknown command. Type h for help.\n");
		}
	}
	return 0;
}
