//
// Created by chris on 8/24/16.
//

#ifndef SHITTYTEXTSEARCH_SNIPPITCREATOR_H
#define SHITTYTEXTSEARCH_SNIPPITCREATOR_H

#include <string>
#include <memory>
#include "TextProcessor.h"

using string = std::string;

class SnippitCreator {
public:
    SnippitCreator(TextProcessor* textProcessor);
    string createSnippet(const string& content, const string& query) const;
private:
    int getMaxWindowStartPosition(const vector<bool>& hits) const;
    string buildSnippet(const vector<string>& contentTokens, const vector<bool>& hits, int startPos, int endPost) const;
    shared_ptr<TextProcessor> textProcessor;
};


#endif //SHITTYTEXTSEARCH_SNIPPITCREATOR_H
