//
// Created by chris on 8/14/16.
//

#ifndef HELLO_WORLD_TOKENVECTORCREATOR_H
#define HELLO_WORLD_TOKENVECTORCREATOR_H

#include <string>
#include <set>
#include <vector>
#include <map>

#include "SparseVector.h"

using namespace std;

class TokenVectorCreator {
public:
    TokenVectorCreator(const vector<string>& all_tokens);
    SparseVector create_sparse_vector(const vector<string>& tokens) const;
private:
    map<string, int> get_count_by_token(const vector<string>& tokens) const;
    map<string, int> _count_by_token;
    map<string, int> _vector_position_by_token;
};


#endif //HELLO_WORLD_TOKENVECTORCREATOR_H
