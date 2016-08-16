#include <boost/algorithm/string.hpp>
#include "TokenCaseConverter.h"

vector<string> TokenCaseConverter::process(const vector<string> &tokens) {
    vector<string> lower_tokens;
    for (string token : tokens) {
        lower_tokens.push_back(boost::algorithm::to_lower_copy(token));
    }
    return lower_tokens;
}
