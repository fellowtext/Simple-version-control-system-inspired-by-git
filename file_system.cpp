#include<iostream>
#include"hashmaps.hpp"
#include"heap.hpp"
#include"file.hpp"
#include"file_system.hpp"
using namespace std;

file_system::file_system(){
    }

file_system::~file_system() {
    // Get a list of all file pointers from the hash map
    std::vector<file*> all_files = top_hash.get_all_files();
    
    // Iterate through the list and delete each one
    for (file* f : all_files) {
        delete f;
    }
}



void file_system::handle_create(string file_name){
        if(top_hash.find_file(file_name)==nullptr){
            file* new_file=new file(file_name);
            top_hash.insert_file(file_name,new_file);
            max_heap_time.insert_file(new_file);
            max_heap_size.insert_file(new_file);
            cout<<"new file created"<<endl;
            return;
        }
        else{
            cout<<"file alreay exist with this name"<<endl;
            return;
        }
    }

void file_system::handle_read(string file_name){
        file* f=top_hash.find_file(file_name);
        if(f!=nullptr){
            string content;
            content=f->read_content();
            cout<< "content is->"<<" "<<content<<endl;
            return;
        }
        else{
            cout<<"no such file"<<endl;
            return;
        }
    }


void file_system::handle_insert(string file_name,string content){
        file* f=top_hash.find_file(file_name);
        if(f==nullptr){
            cout<<"no such file"<<endl;
            return;
        }
        f->insert_content(content);
        max_heap_size.update(f);
        max_heap_time.update(f);
        cout<<"inserted successfully"<<endl;
        return;
    }

void file_system::handle_update(string file_name,string content){
        file* f=top_hash.find_file(file_name);
        if(f==nullptr){
            cout<<"file not found"<<endl;
            return;
        }
        f->update_content(content);
        max_heap_size.update(f);
        max_heap_time.update(f);
        cout<<"content updated successfully"<<endl;
        return;
    }

void file_system::handle_snapshot(string file_name,string msg){
        file* f=top_hash.find_file(file_name);
        if(f==nullptr){
            cout<<"no such file"<<endl;
            return;
        }
        f->create_snapshot(msg);
        max_heap_size.update(f);
        max_heap_time.update(f);
        cout<<"snapshoted successfully"<<endl;
        return;
    }

void file_system::handle_rollback(string file_name,int id){
        file* f=top_hash.find_file(file_name);
        if(id==-1){   //rollback to parent
            bool possible;
            possible=f->roll_back_parent();
            if(possible){
                cout<<"rollbacked to parent version"<<endl;
                return;
            }
            else{
                cout<<"reached at version0 cannot go beyond"<<endl;
                return;
            }

        }

        bool posible=f->roll_back_version(id);
        if(posible){
            cout<<"rollbacked successfully"<<endl;
            return;
        }
        cout<<"invalid id"<<endl;
        return;
    }

void file_system::handle_history(string file_name){
        file* f=top_hash.find_file(file_name);
        if(f==nullptr){
            cout<<"no such file exist"<<endl;
            return;
        }
        vector<version*> history=f->get_history();
        cout<<"here is the history->"<<endl;
        for(int i=history.size()-1;i>=0;i--){
            if(history[i]->snapshot_timestamp!=0){
                tm* time_info = localtime(&history[i]->snapshot_timestamp);
                cout<<time_info->tm_hour<<":"<<time_info->tm_min<<":"<<time_info->tm_sec<<" "<<history[i]->version_id<<" "<<history[i]->message<<endl;
            }
        }
    }

void file_system::handle_recent_files(int num){
        vector<file*> recent=max_heap_time.get_max(num);
        if(recent.size()==0){
            cout<<"non"<<endl;
            return;
        }
        cout<<"here are the files"<<endl;
        for(int i=0;i<recent.size();i++){
            cout<<recent[i]->file_name<<endl;
        }
        return;
    }
void file_system::handle_biggest_trees(int num){
        vector<file*> recent=max_heap_size.get_max(num);
        if(recent.size()==0){
            cout<<"no file is made"<<endl;
            return;
        }
        cout<<"here are the files"<<endl;
        for(int i=0;i<recent.size();i++){
            cout<<recent[i]->file_name<<endl;
        }
        return;
    }

