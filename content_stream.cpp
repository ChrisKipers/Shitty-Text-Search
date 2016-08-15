#include <vector>
#include <string>
#include <boost/filesystem.hpp>
#include <stdexcept>
#include <map>
#include <regex>
#include <fstream>

using namespace std;
using namespace boost::filesystem;

//const regex text_file_regex(".*[.]txt$");
const regex text_file_regex(".*");

vector<string> get_paths_in_dir(string dir_path);

map<string, string> get_content_in_dir(string dir_path) {
    vector<string> paths = get_paths_in_dir(dir_path);
    map<string, string> content_by_path;

    for (vector<string>::iterator iter = paths.begin(); iter != paths.end(); ++iter) {
        ifstream in_file;
        in_file.open(*iter);
        stringstream str_stream;
        str_stream << in_file.rdbuf();
        content_by_path[*iter] = str_stream.str();
    }

    return content_by_path;
}

vector<string> get_paths_in_dir(string dir_path) {
    path root_dir(dir_path);

    if (!exists(root_dir)) {
        throw invalid_argument("Root path doesn't exist");
    }

    if (!is_directory(root_dir)) {
        throw invalid_argument("Root path is not a directory");
    }

    vector<string> text_files;
    for (directory_entry& x : directory_iterator(root_dir)) {
        bool is_txt_extention = regex_match(x.path().string(), text_file_regex);
        if (is_regular_file(x.path()) && is_txt_extention) {
            text_files.push_back(x.path().string());
        }
    }
    return text_files;
}
