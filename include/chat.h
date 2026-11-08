// chat.h
#ifndef CHAT_H
#define CHAT_H

// Key-value pair struct for the chat interface
typedef struct {
	const char *key;
	const char *value;
} KeyValuePair;

int run_chat_engine(void);

extern const KeyValuePair chat_pairs[];
extern const char *vocab_list;

#endif // CHAT_H