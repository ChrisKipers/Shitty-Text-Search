//
// Created by chris on 8/18/16.
//

#include <algorithm>
#include "DocumentRepository.h"

struct DocumentProcessingContainer {
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
    vector<DocumentProcessingContainer> processing_documents;

    vector<string> all_tokens;

    for (const auto& pair : file_contents_by_path) {
        vector<string> tokens = text_processor->process_text(pair.second);
        all_tokens.insert(all_tokens.end(), tokens.begin(), tokens.end());

        DocumentProcessingContainer dpc(std::move(pair.first), std::move(pair.second), std::move(tokens));
        processing_documents.push_back(std::move(dpc));
    }

    token_vector_creator->initialize(all_tokens);

    for (const auto& dpc : processing_documents) {
        vector<string> tokens = std::move(dpc.tokens);
        SparseVector tf_idf_vector =token_vector_creator->create_sparse_vector(tokens);
        IndexedDocument* ix_doc = new IndexedDocument(std::move(dpc.path), std::move(dpc.content), std::move(tf_idf_vector));
        documents.push_back(unique_ptr<IndexedDocument>(ix_doc));
    }
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

