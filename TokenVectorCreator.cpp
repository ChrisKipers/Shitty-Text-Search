#include <algorithm>
#include "TokenVectorCreator.h"

using namespace std;

void TokenVectorCreator::initialize(const vector<string> &all_tokens) {
    _count_by_token = get_count_by_token(all_tokens);

    int pos = 0;
    for (map<string, int>::iterator iter = _count_by_token.begin(); iter != _count_by_token.end(); ++iter) {
        _vector_position_by_token[iter->first] = pos++;
    }
}

SparseVector TokenVectorCreator::create_sparse_vector(const vector<string>& tokens) const {
    map<string, int> count_by_token = get_count_by_token(tokens);
    map<string, double> tf_idf_by_token;

    for (map<string, int>::iterator iter = count_by_token.begin(); iter != count_by_token.end(); ++iter) {
        string token = iter->first;
        try {
            tf_idf_by_token[token] = _count_by_token.at(token) / (1.0 / count_by_token[token]);
        } catch (std::out_of_range e) {
            // token is not in global corpus.
        }
    }

    vector<pair<int, float>> position_and_tf_idfs;

    for (map<string, double>::iterator iter = tf_idf_by_token.begin(); iter != tf_idf_by_token.end(); ++iter) {
        try {
            int pos = _vector_position_by_token.at(iter->first);
            position_and_tf_idfs.push_back(pair<int, double>(pos, iter->second));
        } catch (std::out_of_range e) {
            // token is not in global corpus
        }
    }

    sort(
            position_and_tf_idfs.begin(),
            position_and_tf_idfs.end(),
            [](const pair<int, double>& lhs, const pair<int, double>& rhs) { return lhs.first < rhs.first; });

    vector<int> positions;
    vector<double> values;

    for (pair<int, double> p : position_and_tf_idfs) {
        positions.push_back(p.first);
        values.push_back(p.second);
    }
    SparseVector sv(std::move(positions), std::move(values));
    return sv;
}

map<string, int> TokenVectorCreator::get_count_by_token(const vector<string>& tokens) const {
    map<string, int> count_by_token;
    for (string token : tokens) {
        bool token_is_previous = count_by_token.find(token) != count_by_token.end();
        int current_count = token_is_previous ? count_by_token[token] : 0;
        count_by_token[token] = current_count + 1;
    }
    return count_by_token;
};
