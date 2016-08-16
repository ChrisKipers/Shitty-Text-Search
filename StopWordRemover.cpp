#include "StopWordRemover.h"
#include <fstream>

using namespace std;

// Todo configure this
const string STOP_WORD_FILE_PATH = "/home/chris/ClionProjects/hello-world/refs/stop_words.txt";

StopWordRemover::StopWordRemover() {
    ifstream stop_word_file(STOP_WORD_FILE_PATH);
    for (string line; getline(stop_word_file, line);) {
        _stop_words.insert(line);
    }
};

vector<string> StopWordRemover::process(const vector<string>& tokens) {
    vector<string> filtered_tokens;
    set<string>::iterator end = _stop_words.end();
    for (string token : tokens) {
        if (_stop_words.find(token) == end) {
            filtered_tokens.push_back(token);
        }
    }
    return filtered_tokens;
}