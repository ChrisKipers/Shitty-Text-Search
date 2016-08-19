//
// Created by chris on 8/18/16.
//

#ifndef SHITTYTEXTSEARCH_INDEXEDDOCUMENT_H
#define SHITTYTEXTSEARCH_INDEXEDDOCUMENT_H

#include <string>
#include <vector>

#include "SparseVector.h"

using namespace std;

class IndexedDocument {
public:
    IndexedDocument(
            string file_name,
            string content,
            SparseVector tf_idf_vector);
    const string& getGetFileName() const;
    const string& getContent() const;
    const SparseVector& getTfIdfVector() const;

private:
    string file_name;
    string content;
    SparseVector tf_idf_vector;
};


#endif //SHITTYTEXTSEARCH_INDEXEDDOCUMENT_H
