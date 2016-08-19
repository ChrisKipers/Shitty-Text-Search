//
// Created by chris on 8/18/16.
//

#include "IndexedDocument.h"

IndexedDocument::IndexedDocument(string file_name, string content, SparseVector tf_idf_vector) :
        file_name(file_name), content(content), tf_idf_vector(tf_idf_vector) { }

const string &IndexedDocument::getGetFileName() const {
    return file_name;
}

const string &IndexedDocument::getContent() const {
    return content;
}

const SparseVector &IndexedDocument::getTfIdfVector() const {
    return tf_idf_vector;
}
