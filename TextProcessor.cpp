#include <regex>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>
#include "TextProcessor.h"
#include "TokenCaseConverter.h"
#include "StopWordRemover.h"


const regex punctuation_regex("[[:punct:]]");
const regex multipe_spaces("\\s+");

TextProcessor::TextProcessor() {
    token_modifiers.push_back(unique_ptr<TokenModifier>(new TokenCaseConverter()));
    token_modifiers.push_back(unique_ptr<TokenModifier>(new StopWordRemover()));
}

vector<string> TextProcessor::process_text(const string &content) const {
    string no_punch = remove_punctuation(content);
    auto tokens = tokenize(no_punch);

    for (auto& modifier : token_modifiers) {
        tokens = modifier.get()->process(tokens);
    }
    return tokens;
}

string TextProcessor::remove_punctuation(const string &content) const {
    string no_punc = regex_replace(content, punctuation_regex, "");
    return regex_replace(no_punc, multipe_spaces, " ");
}

vector<string> TextProcessor::tokenize(const string &content) const {
    vector<string> tokens;
    boost::split(tokens, content, boost::is_any_of(" "));
    return tokens;
}
