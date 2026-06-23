#include"tree.hpp"
using namespace std;

version::version(int id,string content,string msg){
        version_id=id;
        this->content=content;
        message=msg;
        created_timestamp=time(nullptr);
        snapshot_timestamp=0;
        parent=nullptr;
    }

////////////////////////////////////////////////////////////////
void version_tree::destroy_tree(version* node) {
    if (node == nullptr) return;
    // First, delete all children
    for (version* child : node->children) {
        destroy_tree(child);
    }
    // Then, delete the node itself
    delete node;
}

version_tree::version_tree(){
        root=new version(0,"","File Created");
        active_version=root;
        active_version->snapshot_timestamp=time(nullptr);   ////the initial 0 version is snapshotted the moment it ca,e to existence
         
    }

version_tree::~version_tree(){
    destroy_tree(root);
}

void version_tree::new_version(int new_id,string msg,string content){
        version* newver=new version(new_id,content,msg);
        newver->parent=active_version;
        active_version->children.push_back(newver);
        active_version=newver;
    }

void version_tree::change_active_version(version* new_active){  //passed argune=ment from the file's verison hashmap
        active_version=new_active;
    }

bool version_tree::rollback_to_parent(){
        if(root!=active_version){
            active_version=active_version->parent;
            return true;
        }
        else{
            return false;
        }
    }

version* version_tree:: get_active_version(){
        return active_version;
    }

vector<version*> version_tree:: get_all_versions(){
        vector<version*> all_versions;
        version* temp=active_version;
        while(temp!=nullptr){
            all_versions.push_back(temp);
            temp=temp->parent;
        }
        return all_versions;
    }

version* version_tree::get_root(){
    return root;
}
