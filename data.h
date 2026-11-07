// data.h
#ifndef DATA_H
#define DATA_H

#define VERSION "v0.1"
#define CLEAR_SCREEN() printf("\033[2J\033[H") // ANSI escape code to clear the screen

#define MAX_TOKENS 255
#define MAX_LENGTH 255

// Key-value pair struct for the chat interface
typedef struct {
	const char *key;
	const char *value;
} KeyValuePair;

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

// Random key-value pairs for the chatbot to use in the chat interface
const KeyValuePair chat_pairs[] = {
    {"hello", "hi"},
    {"hi", "hello"},
    {"hey", "hi"},
    {"greetings", "good day"},
    {"how", "so"},
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
    {"periodic table", "chart that organizes all known elements by their atomic number"},
    {"scientific method", "step by step process scientists use to investigate questions and test ideas"},
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
#endif