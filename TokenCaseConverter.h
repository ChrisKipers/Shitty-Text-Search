#ifndef HELLO_WORLD_TOKENCASECONVERTER_H
#define HELLO_WORLD_TOKENCASECONVERTER_H

#include "TokenModifier.h"

class TokenCaseConverter : public TokenModifier {
public:
    vector<string> process(const vector<string>& tokens);
};


#endif //HELLO_WORLD_TOKENCASECONVERTER_H
