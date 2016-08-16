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

vector<string>* TextProcessor::process_text(const string &content) {
    string no_punch = remove_punctuation(content);
    unique_ptr<vector<string>> tokens(tokenize(no_punch));

    for (TokenModifier* modifier : token_modifiers) {
        tokens.reset(modifier->process(*tokens));
    }
    return tokens.release();
}

string TextProcessor::remove_punctuation(const string &content) {
    string no_punc = regex_replace(content, punctuation_regex, "");
    return regex_replace(no_punc, multipe_spaces, " ");
}

vector<string>* TextProcessor::tokenize(const string &content) {
    vector<string>* tokens = new vector<string>;
    boost::split(*tokens, content, boost::is_any_of(" "));
    return tokens;
}
