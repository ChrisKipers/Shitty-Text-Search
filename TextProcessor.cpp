//
// Created by chris on 8/15/16.
//

#include <regex>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include "TextProcessor.h"
#include "TokenCaseConverter.h"
#include "StopWordRemover.h"

const regex punctuation_regex("[[:punct:]]");
const regex multipe_spaces("\\s+");

TextProcessor::TextProcessor() {
    token_modifiers.push_back(new TokenCaseConverter);
    token_modifiers.push_back(new StopWordRemover);
}

vector<string> TextProcessor::process_text(const string &content) {
    vector<string> tokens  = tokenize(remove_punctuation(content));
    for (TokenModifier* modifier : token_modifiers) {
        tokens = modifier->process(tokens);
    }
    return tokens;
}

string TextProcessor::remove_punctuation(const string &content) {
    string no_punc = regex_replace(content, punctuation_regex, "");
    string no_multi_space = regex_replace(no_punc, multipe_spaces, " ");
    return no_multi_space;
}

vector<string> TextProcessor::tokenize(const string &content) {
    vector<string> tokens;
    boost::split(tokens, content, boost::is_any_of(" "));
    return tokens;
}
