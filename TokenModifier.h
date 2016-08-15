//
// Created by chris on 8/14/16.
//

#ifndef HELLO_WORLD_TOKENMODIFIER_H
#define HELLO_WORLD_TOKENMODIFIER_H

#include <string>
#include <vector>

using namespace std;

class TokenModifier {
public:
    virtual vector<string> process(const vector<string>& tokens) = 0;
};


#endif //HELLO_WORLD_TOKENMODIFIER_H
