#include <iostream>
#include <map>
#include <boost/algorithm/string.hpp>
#include "content_stream.h"
#include "TokenVectorCreator.h"
#include "TextProcessor.h"

using namespace std;

void process_query(
        const string& query,
        const TokenVectorCreator& tvc,
        const map<string, SparseVector>& text_vector_by_path,
        const TextProcessor& text_processor);

void search_repl(
        const TokenVectorCreator& tvc,
        const map<string, SparseVector>& text_vector_by_path,
        const TextProcessor& text_processor);

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cout << "Missing root directory" << endl;
        return 1;
    }

    TextProcessor text_processor;

    map<string, string> file_contents_by_path = get_content_in_dir(argv[1]);
    map<string, vector<string>> tokens_by_path;
    vector<string> all_tokens;

    for (const auto& pair : file_contents_by_path) {
        vector<string> tokens = text_processor.process_text(pair.second);
        tokens_by_path[pair.first] = tokens;
        all_tokens.insert(all_tokens.end(), tokens.begin(), tokens.end());
    }

    TokenVectorCreator tvc(all_tokens);

    map<string, SparseVector> text_vector_by_path;
    for (const auto& pair : tokens_by_path) {
        text_vector_by_path.emplace(pair.first, tvc.create_sparse_vector(pair.second));
    }

    search_repl(tvc, text_vector_by_path, text_processor);

    return 0;
}

void search_repl(const TokenVectorCreator& tvc, const map<string, SparseVector>& text_vector_by_path, const TextProcessor& text_processor) {
    string query = "";
    const string exit_string = "exit()";
    while (true) {
        cout << "Enter query:" << endl;
        getline(cin, query, '\n');

        if (query == exit_string) {
            break;
        }

        process_query(query, tvc, text_vector_by_path, text_processor);
    }
}

void process_query(const string& query, const TokenVectorCreator& tvc, const map<string, SparseVector>& text_vector_by_path, const TextProcessor& text_processor) {
    auto query_tokens = text_processor.process_text(query);
    SparseVector query_vector = tvc.create_sparse_vector(query_tokens);
    vector<pair<string, float>> path_and_score;
    for (map<string, SparseVector>::const_iterator iter = text_vector_by_path.begin();
         iter != text_vector_by_path.end(); ++iter) {
        path_and_score.push_back(pair<string, float>(iter->first, query_vector.angle(iter->second)));
    }

    sort(
            path_and_score.begin(),
            path_and_score.end(),
            [](pair<string, float> lhs, pair<string, float> rhs) { return lhs.second < rhs.second; });

    for (int i = 0; i < path_and_score.size() && i < 5; i++) {
        cout << path_and_score[i].first << " : " << path_and_score[i].second << endl;
    }
}