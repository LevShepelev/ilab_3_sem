#ifndef _CACHE_H  //This is 2Q cache 
#define _CACHE_H


#include <list>
#include <map>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <ctime>
#include <iterator>
#include <cassert>
#include <algorithm>

using namespace std;

const int IN_CODE   = 1;
const int OUT_CODE  = 2;
const int MAIN_CODE = 3;

template<typename T, typename KeyT = int>
class Cache
    {
    struct Node {T data; char list_code = 0; int page_numb = 0;}; //Node: data = page information) 
    using ListIt = typename std::list<Node>::iterator;            //      list_code = number of list, where page is situated
                                                                  //      page_numb = for our comfort, with pages we also keep their numbers
    public:
        Cache(int in_size, int out_size, int main_size) : in_max_size_(in_size), out_max_size_(out_size), main_max_size_(main_size) {}
        void Searching(int page_number);
        void Print_curren_state_of_lists() const;
        long hit_counter_ = 0;
        
    private:
        unordered_map<KeyT, ListIt> hash_;

        list<Node> input_; 
        list<Node> output_;
        list<Node> main_list_;
        long  in_max_size_  = 0;
        long out_max_size_  = 0;
        long main_max_size_ = 0;       

        void Push_to_input(int page_number);
        void Push_to_output(int);
        void Push_to_main_list(int page_number);
        T get_data(int page_number) const;
    };


template <typename T, typename KeyT>
void Cache<T, KeyT>::Searching(int page_number) //The function search newlly enrolled page in lists
    {
    
    if (hash_.count(page_number) == 0)                                              //We have met a new page 
        Push_to_input(page_number);
    else 
        {
        if ((*hash_[page_number]).list_code == IN_CODE)                             //We have met page in Input, due to 2Q algoritm
            {                                                                       //we move it in the beggining of the input_list
            Node buf = *(hash_[page_number]);   
            input_.erase(hash_[page_number]);
            input_.push_front(buf);
            hash_[page_number] = input_.begin();
            }


        else if ((*hash_[page_number]).list_code == OUT_CODE && main_max_size_ > 0) //We have met page in Output, due to 2Q algoritm
                Push_to_main_list(page_number);                                     //we move it to main_lsit    


        else if ((*hash_[page_number]).list_code == MAIN_CODE)                      //We have met page in Main_list, due to 2Q algoritm
            {                                                                       //we move it in the beggining of the main_list
            Node buf = *(hash_[page_number]);
            main_list_.erase(hash_[page_number]);
            main_list_.push_front(buf);
            hash_[page_number] = main_list_.begin();
            }

        hit_counter_++;    
        }
    }

template <typename T, typename KeyT>                   //The function push new page to input_list
void Cache<T, KeyT>::Push_to_input(int page_number)    // if there's no place, it push back element to output_list
    {
    if (in_max_size_ == input_.size())
        {
        Push_to_output(input_.back().page_numb);
        input_.pop_back();
        }
    input_.push_front({get_data(page_number), IN_CODE, page_number});
    hash_[page_number] = input_.begin();
    }


template <typename T, typename KeyT>
void Cache<T, KeyT>::Push_to_output(int page_number)  //The function push page to output_list,
    {                                                 //if there's no place, it delete last output_list element          
    (*hash_[page_number]).list_code = OUT_CODE;
    if (output_.size() == out_max_size_) 
        {
        hash_.erase(output_.back().page_numb);
        output_.pop_back();
        }
    output_.push_front(*(hash_[page_number]));
    hash_[page_number] = output_.begin();
    }


template <typename T, typename KeyT>
void Cache<T, KeyT>::Push_to_main_list(int page_number) //The function push page to main_list,
    {                                                   //if there's no place, it delete last main_list element     
    (*hash_[page_number]).list_code = MAIN_CODE;
    if (main_list_.size() == main_max_size_) 
        {
        hash_.erase(main_list_.back().page_numb);
        main_list_.pop_back();
        }    
    main_list_.splice(main_list_.begin(), output_, hash_[page_number]);
    hash_[page_number] = main_list_.begin();
    }


template <typename T, typename KeyT>
void Cache<T, KeyT>::Print_curren_state_of_lists() const //The function print our lists, and what pages do they contain
    {
    printf("In input, size = %ld\n", input_.size());
    for (auto item : input_)
        printf("%d ", item.page_numb);

    printf("\nIn output, size = %ld\n", output_.size());
    for (auto item : output_)
        printf("%d ", item.page_numb); 

    printf("\nIn main, size = %ld\n", main_list_.size());
    for (auto item : main_list_)
        printf("%d ", item.page_numb); 

    putchar('\n');
    }


template <typename T, typename KeyT>
T Cache<T, KeyT>::get_data(int page_number) const //The function that give us page data from somewhere
    {
    const char example_of_data = 'A';
    return example_of_data;
    }

#endif