#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "chat.h"
#include "util.h"
#include "terminal.h"
#include "main.h"

// Random key-value pairs for the chatbot to use in the chat interface
const KeyValuePair chat_pairs[] = {
    {"hello", "hi"},
    {"hi", "hello"},
    {"hey", "hi"},
    {"greetings", "good day"},
    {"how", "so"},
    {"and", ""},
    {"so", "go on"},
    {"are", "am"},
    {"do", "you"},
    {"is", "is"},
    {"what", "it"},
    {"who", "me"},
    {"where", "here"},
    {"why", "because"},
    {"when", "now"},
    {"wood", "hard, from tree"},
    {"water", "wet, from river"},
    {"fire", "hot, from combustion"},
    {"feel", "don't"},
    {"good", "nice"},
    {"bad", "sad"},
    {"yes", "no"},
    {"no", "yes"},
    {"maybe", "perhaps"},
    {"sure", "ok"},
    {"thanks", "you're welcome"},
    {"thank you", "you're welcome"},
    {"bye", "goodbye"},
    {"goodbye", "bye"},
    {"2+2", "4"},
    {"3*3", "9"},
    {"5-2", "3"},
    {"10/2", "5"},
    {"1+1", "2"},
    {"4*4", "16"},
    {"6-3", "3"},
    {"8/4", "2"},
    {"7+5", "12"},
    {"9*2", "18"},
    {"12-7", "5"},
    {"15/3", "5"},
    {"arithmetic", "branch of mathematics that deals with numbers and operations"},
    {"shapes", "representation of an object's external boundary or outline"},
    {"pemdas", "order of operations used to solve math problems with more than one operation"},
    {"atoms", "building blocks that all matter is made of"},
    {"math", "numbers, addition, subtraction, multiplication, division"},
    {"science", "study of the natural world"},
    {"computer", "electronic device for processing data"},
    {"programming", "writing code for computers"},
    {"you", "simple, a bot"},
    {"life", "nice"},
    {"happy", "good"},
    {"sad", "bad"}
};

const char *vocab_list = 
    "hello\n"
    "hi\n"
    "hey\n"
    "greetings\n"
    "how\n"
    "and"
    "so\n"
    "are\n"
    "do\n"
    "is\n"
    "what\n"
    "who\n"
    "where\n"
    "why\n"
    "when\n"
    "wood\n"
    "water\n"
    "fire\n"
    "feel\n"
    "good\n"
    "bad\n"
    "yes\n"
    "no\n"
    "maybe\n"
    "sure\n"
    "thanks\n"
    "thank you\n"
    "bye\n"
    "goodbye\n"
    "2+2\n"
    "3*3\n"
    "5-2\n"
    "10/2\n"
    "1+1\n"
    "4*4\n"
    "6-3\n"
    "8/4\n"
    "7+5\n"
    "9*2\n"
    "12-7\n"
    "15/3\n"
    "arithmetic\n"
    "shapes\n"
    "pemdas\n"
    "atoms\n"
    "math\n"
    "science\n"
    "computer\n"
    "programming\n"
    "you\n"
    "life\n"
    "happy\n"
    "sad\n";
    
// Runs the chat engine instead of the whole engine being inside an if statement
int run_chat_engine(void){
	clear_screen();
	char input[255];
    char input_copy[255]; // Copy of the input to preserve the original input for punctuation checking

	const char *delimiters = " \t\n.!?,"; // Delimiters for tokenizing the input

	printf("SIMPLEBOT CHAT INTERFACE\n");
	print_chat_help();

	for (;;) {
		printf("> ");
		int chat_result = read_line(input, sizeof(input));
		if (chat_result == 0) {
			return 1;
		}
		if (chat_result == -1) {
			printf("Input too long\n");
			continue;
		}

		strcpy(input_copy, input); // Copy the input to the copy buffer

		for (int i = 0; input[i]; i++) {
			input[i] = tolower((unsigned char)input[i]); // Convert the input to lowercase for easier comparison
		}

		if (strcmp(input, "quit") == 0 || strcmp(input, "end") == 0 || strcmp(input, "exit") == 0) {
			clear_screen();
			break;	
		}

		if (strcmp(input, "h") == 0 || strcmp(input, "help") == 0) {	
			print_chat_help();
			continue;
		}

		if (strcmp(input, "v") == 0 || strcmp(input, "vocab") == 0) {
			printf("Vocabulary list:\n");
			printf("%s", vocab_list);
			continue;
		}

		// Parse the input into words and look it up in a list of key-value structs.
		// No quotation mark support and will not treat it as one word

		char *token = strtok(input, delimiters);
		char answer_buffer[255] = ""; // Buffer to store the answer from the chatbot

		while (token != NULL) {
			const char *value = lookup(token, chat_pairs, sizeof(chat_pairs) / sizeof(chat_pairs[0]));
			const char *peice = value ? value : "not sure"; // If the word is not found, use "not sure" as the answer

			if (strlen(answer_buffer) + strlen(peice) + 2 > sizeof(answer_buffer)) { // Check if the answer buffer will overflow. + 2 is the trailing space and terminator
				break; // Answer is full so we stop here. We could also truncate the answer but that would be messy
			}

			strcat(answer_buffer, peice); // Append the answer to the buffer

            // Note: Only works if before the peice is added to the answer buffer, or the period is before the peice.
            char *match = strstr(input_copy, token); // Find the token in the original input copy
            if (match != NULL) {
                // Get the character right after the token in the original input copy
                char *next_char = match + strlen(token);

                // Check if the next character is a punctuation mark
                if (is_target_punct(*next_char)) {
                    strcat(answer_buffer, "."); // Append a period to the answer buffer if the next character is a punctuation mark
                }
            }

            strcat(answer_buffer, " "); // Append a space to the answer buffer
            
			token = strtok(NULL, delimiters);
		}

		if (!is_empty_or_whitespace(answer_buffer)) {
			printf("%s\n", answer_buffer);
		}
	}
	return 0;
}