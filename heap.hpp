#ifndef HEAP_HPP
#define HEAP_HPP

#include<iostream>
#include<vector>
#include<string>
#include"file.hpp"
using namespace std;

class heap{
private:
    vector<file*> maxheap;
    string mode; //can be time or size
    void heapify_top_down(vector<file*> &heap,int i);

public:
    heap(string m);

    void insert_file(file* new_file);

    vector<file*> get_max(int num);

    void update(file* updated_file);
};



#endif 