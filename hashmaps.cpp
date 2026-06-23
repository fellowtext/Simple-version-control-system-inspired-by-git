#include <iostream>
#include "hashmaps.hpp"
#include "file.hpp"   // Needed here because we actually call File methods
#include "tree.hpp"
#include <vector>
using namespace std;

VersionHash::HashNode::HashNode(version* v_in){
            version_id=v_in->version_id;
            v=v_in;
            next=nullptr;
        }


// VersionHash::VersionHash(version* version_0){       //requires a root version for initia;ization(requires atleat 1 node/version)
//         HashNode* hpointer= new HashNode(version_0);
//         version_map[0]=hpointer;
//     }

VersionHash::VersionHash(){       
        // version* version_0=new version(0,"","File Created");
        // version_0->snapshot_timestamp=time(nullptr);
        // HashNode* hpointer= new HashNode(version_0);
        // version_map[0]=hpointer;
    }

VersionHash::~VersionHash() {
    for (size_t i = 0; i < version_map.size(); ++i) {
        HashNode* entry = version_map[i];
        while (entry != nullptr) {
            HashNode* to_delete = entry;
            entry = entry->next;
            delete to_delete; // Delete the HashNode
        }
    }
}

void VersionHash::Insert_version(version* new_version){
        HashNode* newhp= new HashNode(new_version);
        int index= (newhp->version_id)%100;
        if(version_map[index]==nullptr){
            version_map[index]=newhp;
            return;
        }
        newhp->next=version_map[index];
        version_map[index]=newhp;
    }
version* VersionHash::find_version(int id){
        int index=id%100;
        if (version_map[index]==nullptr){
            return nullptr;
        }
        HashNode* temp=version_map[index];
        while(temp!=nullptr){
            if(temp->version_id==id){
                return temp->v;
            }
            temp=temp->next;
        }
        return nullptr;
    }




Hashfile::HashfileNode::HashfileNode(string fname,file* fin){
            f=fin;
            file_name=fname;
            next=nullptr;
        }

Hashfile::Hashfile(){
    }

Hashfile::~Hashfile() {
    for (int i = 0; i < file_map.size(); ++i) {
        HashfileNode* entry = file_map[i];
        while (entry != nullptr) {
            HashfileNode* to_delete = entry;
            entry = entry->next;
            delete to_delete; // Delete the HashNode
        }
    }
}

vector<file*> Hashfile::get_all_files() {
    vector<file*> all_files;
    for (size_t i = 0; i < file_map.size(); ++i) {
        HashfileNode* entry = file_map[i];
        while (entry != nullptr) {
            all_files.push_back(entry->f);
            entry = entry->next;
        }
    }
    return all_files;
}

size_t Hashfile::hashindex(string s){
        size_t index=0;
        int prime=31;
        if(s.size()!=0){
            for(int i=s.size()-1;i>=0;i--){
                index=index*prime +s[i];
            }
        }
        index=index%100;
        return index;   
    }

void Hashfile::insert_file(string new_file_name,file*new_file){
        HashfileNode* newnode=new HashfileNode(new_file_name,new_file);
        size_t index=hashindex(new_file_name);
        if(file_map[index]==nullptr){
            file_map[index]=newnode;
        }
        else{
            newnode->next=file_map[index];
            file_map[index]=newnode;
        }
    }

file* Hashfile::find_file(string file_name_in){
        size_t index=hashindex(file_name_in);
        if(file_map[index]==nullptr){
            return nullptr;
        }
        HashfileNode* temp= file_map[index];
        while(temp!=nullptr){
            if(temp->file_name==file_name_in){
                return temp->f;
            }
            temp=temp->next;
        }
        return nullptr;
    }

