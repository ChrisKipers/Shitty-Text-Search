//
// Created by chris on 8/18/16.
//

#ifndef SHITTYTEXTSEARCH_CONTENTLOADER_H
#define SHITTYTEXTSEARCH_CONTENTLOADER_H

#include <map>
#include <string>
#include <vector>

using namespace std;

class ContentLoader {
public:
    map<string, string> get_contents_by_path_name(const string& dir_path) const;
private:
    vector<string> get_paths_in_dir(string dir_path) const;
};


#endif //SHITTYTEXTSEARCH_CONTENTLOADER_H
