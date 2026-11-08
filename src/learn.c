#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "learn.h"
#include "util.h"
#include "terminal.h"
#include "main.h"

// List of topics, mostly sourced from Wikipedia
const char *topics[] = {
    "Arithmetic is a branch of mathematics that deals with operations like addition, subtraction, multiplication, and division.\n"
    "Arithmetic is very important in day to day life.\n"
    "Here are 2 examples: 9 + 9 = 18, 5 * 5 = 25\n",
    
    "Shapes are a representation of an object's external boundary or outline.\n"
    "Simple shapes typically make up our life, such as a square TV or a rectangle.\n"
    "A few examples of shapes would be a square (4 corners, 4 equal length sides), a triangle (3 corners, 3 sides),"
    "and a rectangle (4 corners, 2 pairs of equal length sides but the pairs"
    "are different lengths)\n",

    "PEMDAS is the order of operations used to solve math problems with more than one operation.\n"
    "It stands for Parentheses, Exponents, Multiplication, Division, Addition, and Subtraction.\n"
    "Multiplication and division share the same level and are done left to right, and so do addition and subtraction.\n"
    "Here are 2 examples: 2 + 3 * 4 = 14 (multiply first), (2 + 3) * 4 = 20 (parentheses first)\n",

    "The periodic table is a chart that organizes all known elements by their atomic number, which is how many protons are in that atom.\n"
    "Elements in the same column have similar properties, and each element has a one or two letter symbol.\n"
    "Some examples of elements on the table would be hydrogen (H, atomic number 1), carbon (C, atomic number 6), and oxygen (O, atomic number 8)\n",

    "The scientific method is a step by step process scientists use to investigate questions and test ideas.\n"
    "The basic steps are: ask a question, do research, form a hypothesis, test it with an experiment, analyze the results, and share the conclusion.\n"
    "For example, you could question if a sunflower grows faster with more light, do research about it, form a hypothesis, test it with different levels of light,"
    "and share the conclusion\n",
    
    "Atoms are building blocks that all matter is made of.\n"
    "An atom has a nucleus in the center made of protons (positive charge) and neutrons (no charge), with electrons (negative charge) moving around the outside.\n"
    "3 examples of atoms would be a hydrogen atom (1 proton, 1 electron), a helium atom (2 protons, 2 neutrons, 2 electrons), and a carbon atom (6 protons, 6 neutrons, 6 electrons)\n"
};

int run_learning_engine(void){
	clear_screen();
	printf("SIMPLEBOT LEARNING ENGINE\n");
	printf("Quick overviews of topics, with examples\n");

	print_learn_help();
	
	char line[255];
	size_t limit = sizeof(topics) / sizeof(topics[0]) - 1; // Dynamic limit of topics, not hardcoded so I dont have to update this everytime a new topic comes by. Subtract by 1 so it's the index limit not number of topics
	
	for (;;) {
		printf("> ");

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
			clear_screen();
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
			if (!is_empty_or_whitespace(line)) {
				printf("No letter chosen. Enter help to see letters\n");
				continue;
			}
			continue;
		}
	}
	return 0;
}