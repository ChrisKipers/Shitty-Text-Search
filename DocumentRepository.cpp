//
// Created by chris on 8/18/16.
//

#include <algorithm>
#include <atomic>
#include <boost/thread/thread.hpp>
#include "DocumentRepository.h"

struct DocumentProcessingContainer {
    DocumentProcessingContainer() {};
    DocumentProcessingContainer(string path, string content, vector<string> tokens):
            path(path), content(content), tokens(tokens) {};
    string path;
    string content;
    vector<string> tokens;
};

DocumentRepository::DocumentRepository(
        ContentLoader* content_loader,
        TextProcessor* text_processor,
        TokenVectorCreator* token_vector_creator,
        DocumentRanker* document_ranker) :
        content_loader(content_loader),
        text_processor(text_processor),
        token_vector_creator(token_vector_creator),
        document_ranker(document_ranker) { }

void DocumentRepository::loadDocumentsFromDirectory(const string &path_to_directory) {
    map<string, string> file_contents_by_path = content_loader->get_contents_by_path_name(path_to_directory);
    vector<DocumentProcessingContainer> processing_documents = getDocumentProcessingContiner(file_contents_by_path);

    vector<string> all_tokens;

    for (const auto& dpc : processing_documents) {
        vector<string> tokens = dpc.tokens;
        all_tokens.insert(all_tokens.end(), tokens.begin(), tokens.end());
    }

    token_vector_creator->initialize(all_tokens);

    atomic<long> index(0);
    documents.resize(processing_documents.size());

    auto create_index_document_lambda = [&]() {
        long current_index = index++;
        while (current_index < processing_documents.size()) {
            DocumentProcessingContainer& dpc = processing_documents[current_index];
            SparseVector tf_idf_vector =token_vector_creator->create_sparse_vector(std::move(dpc.tokens));
            IndexedDocument* ix_doc = new IndexedDocument(std::move(dpc.path), std::move(dpc.content), std::move(tf_idf_vector));
            documents[current_index]  =unique_ptr<IndexedDocument>(ix_doc);
            current_index = index++;
        }
    };

    int num_of_workers = 4;
    boost::thread_group workers;
    for (int i = 0; i < num_of_workers; i++) {
        workers.create_thread(create_index_document_lambda);
    }
    workers.join_all();

}

vector<DocumentProcessingContainer>
DocumentRepository::getDocumentProcessingContiner(const map<string, string> &file_contents_by_path) const {
    vector<string> keys;
    for (const auto& pair : file_contents_by_path) {
        keys.push_back(pair.first);
    }
    vector<DocumentProcessingContainer> processing_documents(keys.size());

    atomic<long> index(0);
    auto worker_lambda = [&]() {
        long current_index = index++;
        while (current_index < keys.size()) {
            string path = keys[current_index];
            string content = file_contents_by_path.at(path);
            vector<string> tokens = text_processor->process_text(content);
            processing_documents[current_index] =DocumentProcessingContainer(path, content, std::move(tokens));
            current_index = index++;
        }
    };

    int num_of_workers = 4;
    boost::thread_group workers;
    for (int i = 0; i < num_of_workers; i++) {
        workers.create_thread(worker_lambda);
    }
    workers.join_all();

    return processing_documents;
}

const vector<IndexedDocument*> DocumentRepository::queryDocuments(const string &query, const int& max_number_of_results) const {
    vector<IndexedDocument*> indexed_doc_refs(documents.size());
    for (int i = 0; i < documents.size(); i++) {
        indexed_doc_refs[i] = documents[i].get();
    }
    vector<float> document_scores = document_ranker->score_documents(query, indexed_doc_refs);
    vector<pair<int, float>> scores_and_index(document_scores.size());
    for (int i = 0; i < document_scores.size(); i++) {
        scores_and_index[i] = pair<int, float>(i, document_scores[i]);
    }

    sort(
            scores_and_index.begin(),
            scores_and_index.end(),
            [](pair<int, float> lhs, pair<int, float> rhs) { return lhs.second < rhs.second; });

    vector<IndexedDocument*> top_results(min<int>(scores_and_index.size(), max_number_of_results));

    for (int i = 0; i < top_results.size(); i++) {
        int result_index = scores_and_index[i].first;
        top_results[i] = indexed_doc_refs[result_index];
    }
    return top_results;
}

