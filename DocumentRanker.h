//
// Created by chris on 8/18/16.
//

#ifndef SHITTYTEXTSEARCH_DOCUMENTRANKER_H
#define SHITTYTEXTSEARCH_DOCUMENTRANKER_H


#include "IndexedDocument.h"
#include "TokenVectorCreator.h"
#include "TextProcessor.h"

class DocumentRanker {
public:
    DocumentRanker(TokenVectorCreator* token_vector_creator, TextProcessor* text_processor);
    vector<float> score_documents(const string& query, const vector<IndexedDocument*>& documents) const;
private:
    shared_ptr<TokenVectorCreator> token_vector_creator;
    shared_ptr<TextProcessor> text_processor;
};


#endif //SHITTYTEXTSEARCH_DOCUMENTRANKER_H
