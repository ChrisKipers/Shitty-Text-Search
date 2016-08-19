#include "DocumentRanker.h"

DocumentRanker::DocumentRanker(TokenVectorCreator* token_vector_creator, TextProcessor* text_processor) :
        token_vector_creator(token_vector_creator), text_processor(text_processor) {}

vector<float> DocumentRanker::score_documents(const string &query, const vector<IndexedDocument*>& documents) const {
    auto query_tokens = text_processor->process_text(query);
    SparseVector query_vector = token_vector_creator->create_sparse_vector(query_tokens);
    vector<float> document_scores;

    for (const IndexedDocument* document : documents) {
        document_scores.push_back(query_vector.angle(document->getTfIdfVector()));
    }

    return document_scores;
}
