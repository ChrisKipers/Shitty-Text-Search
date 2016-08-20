#include "DocumentRanker.h"
#include <boost/thread/thread.hpp>
#include <atomic>

DocumentRanker::DocumentRanker(TokenVectorCreator* token_vector_creator, TextProcessor* text_processor) :
        token_vector_creator(token_vector_creator), text_processor(text_processor) {}

vector<float> DocumentRanker::score_documents(const string &query, const vector<IndexedDocument*>& documents) const {
    auto query_tokens = text_processor->process_text(query);
    SparseVector query_vector = token_vector_creator->create_sparse_vector(query_tokens);
    vector<float> document_scores(documents.size());

    std::atomic<long> index(0);

    boost::thread_group workers;
    auto worker_lambda = [&]() {
        long current_index = index++;
        while ( current_index < document_scores.size()) {
            document_scores[current_index] = query_vector.angle(documents[current_index]->getTfIdfVector());
            current_index = index++;
        }
    };

    int number_of_workers = 4;
    for (int i = 0; i < number_of_workers; i++) {
        workers.create_thread(worker_lambda);
    }
    workers.join_all();
    return document_scores;
}
