#include<iostream>
#include "file.hpp"
#include "hashmaps.hpp"


using namespace std;



file::file(string name){
        file_name=name;
        version* root =file_tree.get_root();
        version_index.Insert_version(root);
        total_versions=1;   //version 0 having no content
        last_modification_time=time(nullptr);
    }

    
string file::read_content(){
        version* active_ver= file_tree.get_active_version();
        string content =active_ver->content;
        return content;
    }

void file::insert_content(string new_content){                                  //snapshot is implimented implicitly
        version* active_ver=file_tree.get_active_version();
        if(active_ver->snapshot_timestamp==0){//never snapshoted
            active_ver->content+=new_content;
            last_modification_time=time(nullptr);
            return;
        }

        else{//the active_node is snapshotted
            file_tree.new_version(total_versions,"","");
            active_ver=file_tree.get_active_version();
            active_ver->content+=new_content;
            version_index.Insert_version(active_ver);
            last_modification_time=time(nullptr);
            total_versions+=1;
            return;
        }

    }

void file::update_content(string new_content){
        version* active_ver=file_tree.get_active_version();
        if(active_ver->snapshot_timestamp==0){//never snapshoted
            active_ver->content=new_content;
            last_modification_time=time(nullptr);
            return;
        }

        else{//the active_node is snapshotted
            file_tree.new_version(total_versions,"","");
            active_ver=file_tree.get_active_version();
            active_ver->content=new_content;
            version_index.Insert_version(active_ver);
            last_modification_time=time(nullptr);
            total_versions+=1;
            return;
        }
    }

void file::create_snapshot(string msg){
        version* active_ver=file_tree.get_active_version();
        if(active_ver->snapshot_timestamp==0){
            active_ver->message=msg;
            active_ver->snapshot_timestamp=time(nullptr);
            last_modification_time=time(nullptr);
            return;
        }
        else{
            return;
        }
    }

bool file::roll_back_version(int id){
        version* new_active=version_index.find_version(id);
        if(new_active!=nullptr){
            file_tree.change_active_version(new_active);
            return true;
        }
        else{
            return false;
        }
    }

bool file::roll_back_parent(){
        bool done;
        done=file_tree.rollback_to_parent();
        if(done==true){
            return true;
        }
        return false;
    }

vector<version*> file::get_history(){
        vector<version*> version_order =file_tree.get_all_versions();
        return version_order;
    }

int file::get_total_versions(){
        return total_versions;
    }

time_t file::get_last_modification_time(){
        return last_modification_time;
    }
