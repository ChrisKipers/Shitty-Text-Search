#ifndef HELLO_WORLD_TEXTPROCESSOR_H
#define HELLO_WORLD_TEXTPROCESSOR_H

#include <string>
#include <vector>
#include "TokenModifier.h"

using namespace std;

class TextProcessor {
public:
    TextProcessor();
    ~TextProcessor();
    vector<string>* process_text(const string& content);

private:
    string remove_punctuation(const string& content);
    vector<string>* tokenize(const string& content);
    vector<TokenModifier*> token_modifiers;
};


#endif //HELLO_WORLD_TEXTPROCESSOR_H
