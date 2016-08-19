#include "ContentLoader.h"

#include <boost/filesystem.hpp>
#include <stdexcept>
#include <regex>
#include <fstream>

using namespace std;
using namespace boost::filesystem;

//const regex text_file_regex(".*[.]txt$");
const regex text_file_regex(".*");

map<string, string> ContentLoader::get_contents_by_path_name(const string &dir_path) const {
    vector<string> paths = get_paths_in_dir(dir_path);
    map<string, string> content_by_path;

    for (const string& path : paths) {
        ifstream in_file;
        in_file.open(path);
        stringstream str_stream;
        str_stream << in_file.rdbuf();
        content_by_path[path] = str_stream.str();
    }

    return content_by_path;
}

vector<string> ContentLoader::get_paths_in_dir(string dir_path) const {
    path root_dir(dir_path);

    if (!exists(root_dir)) {
        throw invalid_argument("Root path doesn't exist");
    }

    if (!is_directory(root_dir)) {
        throw invalid_argument("Root path is not a directory");
    }

    vector<string> text_files;
    for (const directory_entry& x : directory_iterator(root_dir)) {
        bool is_txt_extention = regex_match(x.path().string(), text_file_regex);
        if (is_regular_file(x.path()) && is_txt_extention) {
            text_files.push_back(x.path().string());
        }
    }
    return text_files;
}
