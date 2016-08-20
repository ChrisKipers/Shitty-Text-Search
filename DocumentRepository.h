#ifndef SHITTYTEXTSEARCH_DOCUMENTREPOSITORY_H
#define SHITTYTEXTSEARCH_DOCUMENTREPOSITORY_H

#include <string>

#include "ContentLoader.h"
#include "IndexedDocument.h"
#include "TokenVectorCreator.h"
#include "TextProcessor.h"
#include "DocumentRanker.h"

using namespace std;

struct DocumentProcessingContainer;

class DocumentRepository {
public:
    DocumentRepository(
            ContentLoader* content_loader,
            TextProcessor* text_processor,
            TokenVectorCreator* token_vector_creator,
            DocumentRanker* document_ranker
    );
    DocumentRepository(const DocumentRepository& rhs) = delete;
    void loadDocumentsFromDirectory(const string& path_to_directory);
    const vector<IndexedDocument*> queryDocuments(const string& query, const int& max_number_of_results) const;

private:
    vector<DocumentProcessingContainer> getDocumentProcessingContiner(const map<string, string>& file_contents_by_path) const;
    vector<unique_ptr<IndexedDocument>> documents;
    shared_ptr<TokenVectorCreator> token_vector_creator;
    shared_ptr<ContentLoader> content_loader;
    shared_ptr<TextProcessor> text_processor;
    shared_ptr<DocumentRanker> document_ranker;
};


#endif //SHITTYTEXTSEARCH_DOCUMENTREPOSITORY_H
