#ifndef HASHMAP_HPP
#define HASHMAP_HPP
#include"tree.hpp"

class file;  // Forward declaration (enough since only using File*)

struct VersionHash{
    struct HashNode{                    //a hashnode which will be used for making linkedlists
    public:
        int version_id;
        version* v;
        HashNode* next;
        HashNode(version* v_in);
    };
private:
    vector<HashNode*> version_map{vector<HashNode*>(100, nullptr) };  //something new 
public:
    // VersionHash(version* version_0){};
    VersionHash();     //now it does not take version0 as a input for initializing a hashmap

    ~VersionHash();

    void Insert_version(version* new_version);

    version* find_version(int id);

};



struct Hashfile{

    struct HashfileNode{                    //a hashnode which will be used for making linkedlists
    public:
        string file_name;
        file* f;
        HashfileNode* next;
        HashfileNode(string fname,file* fin);
    };
private:
    vector<HashfileNode*> file_map{vector<HashfileNode*>(100,nullptr)};
public:
    Hashfile();

    ~Hashfile();

    vector<file*>get_all_files();

    size_t hashindex(string s);

    void insert_file(string new_file_name,file*new_file);

    file* find_file(string file_name_in);

};

#endif 