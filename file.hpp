#ifndef FILE_HPP
#define FILE_HPP
#include "hashmaps.hpp"   // Needed because File contains a full Hash object
#include"tree.hpp"
using namespace std;

class file{
public:
    int total_versions;
    time_t last_modification_time;
    VersionHash version_index;               //hash from the id to the version
    version_tree file_tree;                  // all versions with root and active_version
    string file_name;
    file(string name);

    string read_content();
    
    void insert_content(string new_content);                                 //snapshot is implimented implicitly

    void update_content(string new_content);

    void create_snapshot(string msg);

    bool roll_back_version(int id);

    bool roll_back_parent();

    vector<version*> get_history();

    int get_total_versions();

    time_t get_last_modification_time();

};
#endif