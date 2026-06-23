#include<iostream>
#include<vector>
#include<string>
#include"file.hpp"
#include"heap.hpp"
using namespace std;

void heap::heapify_top_down(vector<file*> &heap,int i){
        int n=heap.size();
        int top=i;
        int left=2*i+1;
        int right=2*i+2;
        int candidate=top;

        if(mode=="time"){
            if(left<=n-1&&heap[left]->last_modification_time>heap[candidate]->last_modification_time){
                candidate=left;
            }
            if(right<=n-1&&heap[right]->last_modification_time>heap[candidate]->last_modification_time){
                candidate=right;
            }
            if(candidate!=top){
                swap(heap[top],heap[candidate]);
                heapify_top_down(heap,candidate);
            }
        }    

        else if(mode=="size"){

            if(left<=n-1&&heap[left]->total_versions>heap[candidate]->total_versions){
                candidate=left;
            }
            if(right<=n-1&&heap[right]->total_versions>heap[candidate]->total_versions){
                candidate=right;
            }
            if(candidate!=top){
                swap(heap[top],heap[candidate]);
                heapify_top_down(heap,candidate);
            }
        }
    }


heap::heap(string m){
        mode=m;
    }

void heap::insert_file(file* new_file){
        maxheap.push_back(new_file);
        int curr=maxheap.size()-1;
        int parent=(curr-1)/2;
        if(mode=="time"){
            while(maxheap[parent]->last_modification_time<maxheap[curr]->last_modification_time){
                swap(maxheap[parent],maxheap[curr]);
                curr=parent;
                if(curr==0){
                    break;
                }
                else{
                    parent=(curr-1)/2;
                }
            }
        }
        else if(mode=="size"){
            while(maxheap[parent]->total_versions<maxheap[curr]->total_versions){
                swap(maxheap[parent],maxheap[curr]);
                curr=parent;
                if(curr==0){
                    break;
                }
                else{
                    parent=(curr-1)/2;
                }
            }
        }
    }

vector<file*> heap::get_max(int num){
        vector<file*> list;
        vector<file*> copy=maxheap;
        for(int i=0;i<num;i++){
            list.push_back(copy[0]);
            swap(copy[0],copy.back());
            copy.pop_back();
            heapify_top_down(copy,0);
        }
        return list;
    }

void heap::update(file* updated_file){
    int n=maxheap.size();
    int index=-1;
    for(int i=0;i<n;i++){
        if(maxheap[i]==updated_file){
            index=i;
            break;
        }
    }
    if(index==-1){
        return;
    }

    int parent=(index-1)/2;
        if(mode=="time"){
            while(maxheap[parent]->last_modification_time<maxheap[index]->last_modification_time){
                swap(maxheap[parent],maxheap[index]);
                index=parent;
                if(index==0){
                    break;
                }
                else{
                    parent=(index-1)/2;
                }
            }
            heapify_top_down(maxheap,index);

        }
        else if(mode=="size"){
            while(maxheap[parent]->total_versions<maxheap[index]->total_versions){
                swap(maxheap[parent],maxheap[index]);
                index=parent;
                if(index==0){
                    break;
                }
                else{
                    parent=(index-1)/2;
                }
            }
            heapify_top_down(maxheap,index);
        }
}