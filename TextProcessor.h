#ifndef HELLO_WORLD_TEXTPROCESSOR_H
#define HELLO_WORLD_TEXTPROCESSOR_H

#include <string>
#include <vector>
#include "TokenModifier.h"

using namespace std;

class TextProcessor {
public:
    TextProcessor();
    vector<string> process_text(const string& content) const;

private:
    string remove_punctuation(const string& content) const;
    vector<string> tokenize(const string& content) const;
    vector<unique_ptr<TokenModifier>> token_modifiers; // mut be reference for polymorphism :(
};


#endif //HELLO_WORLD_TEXTPROCESSOR_H
