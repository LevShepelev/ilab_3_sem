#ifndef _IDEAL_CACHE_H   //This is an ideal cache that knows in what order pages will be served to it 
#define _IDEAL_CACHE_H


#include <list>
#include <map>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <ctime>
#include <iterator>
#include <cassert>
#include <algorithm>
#include <vector>

using namespace std;

template <typename T, typename KeyT = int>
class Ideal_cache 
    {
    struct Node {T data; int distance; int page_numb;};
    using ListIt = typename std::list<Node>::iterator;
    
    public:
        Ideal_cache(int size) : input_max_size_(size) {}
        void Reading_pages(KeyT page_number, int page_position)             //The function for filling map positions_
                { positions_[page_number].push_back(page_position); } 
        void Searching(int page_number, int position);                      //The function search pages in list                                         
        T get_data(int page_number) const;  
                                        //The function return page information 
        int hit_counter_ = 0;

    private:
        int Find_distance(int page_number, int position);                   //The function finds distance between curent page and 
                                                                            // position where this page will be met again in future
        long input_max_size_ = 0;
        list<Node> input_;
        unordered_map<KeyT, vector<int>> positions_;
        unordered_map<KeyT, ListIt> hash_;
       
    };

template <typename T, typename KeyT>
void Ideal_cache<T, KeyT>::Searching(int page_number, int position)
    {
    if (hash_.count(page_number) == 0)                                            
        {
        int distance = Find_distance(page_number, position);
        assert(distance != -2);
        input_.sort([](const Node& first, const Node& second) { return first.distance < second.distance;});
        if (distance < input_.back().distance || input_.size() < input_max_size_)
            {
            if (input_.size() == input_max_size_ && input_.size() > 0)
                {
                hash_.erase(input_.back().page_numb);
                input_.pop_back();
                }
            input_.push_front({get_data(page_number), distance, page_number});
            hash_[page_number] = input_.begin();
            }
        }
    else 
        hit_counter_++;
    }


template <typename T, typename KeyT>
int Ideal_cache<T, KeyT>::Find_distance(int page_number, int position)
    {
    for (int i = 0; i < (positions_[page_number]).size(); i++)
        {
        if ((positions_[page_number])[i] > position)
            return  (positions_[page_number])[i] - position;
        else return -1;
        }
    return -2;
    }


template <typename T, typename KeyT>
T Ideal_cache<T, KeyT>::get_data(int page_number) const //The function that give us page data from somewhere
    {
    const char example_of_data = 'A';
    return example_of_data;
    }


#endif