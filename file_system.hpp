#ifndef FILE_SYSTEM_HPP
#define FILE_SYSTEM_HPP

#include"hashmaps.hpp"
#include"heap.hpp"
#include"file.hpp"
using namespace std;

class file_system{
private:
    Hashfile top_hash;
    heap max_heap_time=heap("time");
    heap max_heap_size=heap("size");
public:
    file_system();

    ~file_system();

    void handle_create(string file_name);

    void handle_read(string file_name);


    void handle_insert(string file_name,string content);


    void handle_update(string file_name,string content);

    void handle_snapshot(string file_name,string msg);

    void handle_rollback(string file_name,int id);


    void handle_history(string file_name);

    void handle_recent_files(int num);

    void handle_biggest_trees(int num);
};



#endif 