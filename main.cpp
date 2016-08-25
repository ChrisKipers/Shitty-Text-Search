#include <iostream>
#include <map>
#include <boost/algorithm/string.hpp>
#include "TokenVectorCreator.h"
#include "TextProcessor.h"
#include "DocumentRepository.h"
#include "SnippitCreator.h"

using namespace std;

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Missing root directory" << endl;
        return 1;
    }
    // TODO: move to factory
    ContentLoader* cl =new ContentLoader;
    TextProcessor* tp = new TextProcessor;
    TokenVectorCreator* tvc = new TokenVectorCreator;
    DocumentRanker* dr = new DocumentRanker(tvc, tp);
    DocumentRepository document_repository(cl, tp, tvc, dr);

    SnippitCreator sp(tp);

    document_repository.loadDocumentsFromDirectory(argv[1]);

    string query = "";
    const string exit_string = "exit()";
    while (true) {
        cout << "Enter query:" << endl;
        getline(cin, query, '\n');

        if (query == exit_string) {
            break;
        }

        vector<IndexedDocument*> results = document_repository.queryDocuments(query, 5);
        for (const auto* result : results) {
            cout << result->getGetFileName() << endl;
            cout << sp.createSnippet(result->getContent(), query) << endl << endl;
        }
    }

    return 0;
}
