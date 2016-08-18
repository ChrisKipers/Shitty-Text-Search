#ifndef HELLO_WORLD_STOPWORDREMOVER_H
#define HELLO_WORLD_STOPWORDREMOVER_H

#include <set>
#include <string>
#include "TokenModifier.h"

class StopWordRemover : public TokenModifier {
public:
    StopWordRemover();
    vector<string> process(const vector<string>& tokens) const;
private:
    set<string> _stop_words;
};


#endif //HELLO_WORLD_STOPWORDREMOVER_H
