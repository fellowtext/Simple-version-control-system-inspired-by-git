#ifndef TREE_HPP
#define TREE_HPP
#include<vector>
#include<queue>
#include<ctime>
#include<string>
using namespace std;


class version{
public:
    int version_id;
    string content;
    string message;
    time_t created_timestamp;
    time_t snapshot_timestamp;
    version* parent;
    vector<version*> children;
    version(int id,string content,string msg);
};

struct version_tree{
private:
    version* root;
    version* active_version;
    void destroy_tree(version* node);
public:
    version_tree();

    ~version_tree();

    void new_version(int new_id,string msg,string content);

    void change_active_version(version* new_active);

    bool rollback_to_parent();

    version* get_active_version();

    vector<version*> get_all_versions();

    version* get_root();
};

#endif 