#pragma once
#include <algorithm>
#include <iostream>
#include <iostream>
#include <fstream>

template <typename T>
class Tree final
    {
    struct Node_t
        {
        Node_t(T key, Node_t* prev) : key(key), prev(prev) {}
        Node_t(Node_t* node) : key(node -> key), height(node -> height), under(node -> under) {}
        T key;
        Node_t* left = nullptr;
        Node_t* right = nullptr;
        Node_t* prev = nullptr;
        int height = 1;
        int under = 0; // under shows us, how many nodes under this node
        };
    

    public:
        Tree() {}
        Tree(const Tree& tr);
        Tree(Tree&& tr) noexcept;
        Tree& operator= (const Tree& tr);
        Tree& operator= (Tree&& tr) noexcept;
        ~Tree();

        void Insert(T key);
        void Erase(T key);
        void Print_tree_to_graphiz() const;
        void Print_tree(Node_t* node, std::ofstream& fout) const;
        void Graphiz_translation(Node_t* node, std::ofstream& fout) const;
        int K_least_element(int k) const noexcept;
        int Numb_of_elem_less_than(int key) const noexcept;
        int Get_size() const noexcept { return Under(root_); } 

    private: 
        Node_t* root_ = nullptr;
        int  Height(Node_t* curr) const noexcept { return curr ? curr -> height : 0; }
        int  Under(Node_t* curr)  const noexcept { return curr ? curr -> under + 1 : 0; }
        int  Balance_index(Node_t* curr) const noexcept { return Height(curr -> right) - Height(curr -> left); }
        int  Count_height(Node_t* curr) const noexcept;
        void Update_height(Node_t* curr) noexcept;
        void Rotate_right(Node_t* curr) noexcept;
        void Rotate_left(Node_t* curr) noexcept; 
        void Height_update_lift(Node_t* curr) noexcept;
        void Rebalance(Node_t* curr) noexcept;
        void Clear() noexcept;
        void Delete_if_right_is_not_empty(Node_t* curr);
        void Delete_if_right_is_empty_but_left_not(Node_t* curr);
        Node_t* Search_min(Node_t* curr) const noexcept;
        Node_t* Find_nearest_node(T key) const noexcept;
        Node_t* Find_elem(T key) const noexcept; 

    };


template <typename T>
Tree<T>::~Tree()
    {
    while (root_ != nullptr)
        {
        if (root_ -> left != nullptr)
            root_ = root_ -> left;
        else if (root_ -> right != nullptr)  
            root_ = root_ -> right;
        else 
            {
            Node_t* tmp = root_ -> prev;
            if (tmp == nullptr)
                delete root_;
            else if (tmp -> left == root_)
                {
                tmp -> left = nullptr;
                delete root_;
                }
            else 
                {
                tmp -> right = nullptr;
                delete root_;
                }
            root_ = tmp;
            }
        }
    }



//Copy constructor
template <typename T>
Tree<T>::Tree(const Tree& tr)
    {
    Node_t* nd_1 = tr.root_;
    try {
        root_ = new Node_t(nd_1);
        Node_t* nd_2 = root_;
        while (nd_1 != nullptr)
            {
            if (nd_1 -> left != nullptr && nd_2 -> left == nullptr)
                {
                nd_2 -> left = new Node_t(nd_1 -> left);
                nd_2 -> left -> prev = nd_2;
                nd_1 = nd_1 -> left;
                nd_2 = nd_2 -> left;
                }
            else if (nd_1 -> right != nullptr && nd_2 -> right == nullptr)
                {
                nd_2 -> right = new Node_t(nd_1 -> right);
                nd_2 -> right -> prev = nd_2;
                nd_1 = nd_1 -> right;
                nd_2 = nd_2 -> right;
                }
            else 
                {
                nd_1 = nd_1 -> prev;
                nd_2 = nd_2 -> prev;
                }
            }
        }
    catch(...) { Clear();  throw;}
    }


// Move constructor
template <typename T>
Tree<T>::Tree(Tree&& tr) noexcept
    {
    std::swap(tr.root_, root_);
    }


template <typename T>
Tree<T>& Tree<T>::operator= (const Tree& tr)
    {
    if (this == &tr)
        return *this;
    Tree<T> tmp(tr);
    std::swap(tmp.root_, root_);
    return *this;
    } 


template <typename T>
Tree<T>& Tree<T>::operator= (Tree&& tr) noexcept
    {
    if (this == &tr)
        return *this;
    std::swap(root_, tr.root_);
    return *this;
    }


template <typename T>
void Tree<T>::Update_height(Node_t* curr) noexcept
    {
    int h_left =  Height(curr -> left);
    int h_right = Height(curr -> right);
    curr -> under  = Under(curr -> left) + Under(curr -> right);
    curr -> height = (h_left > h_right ? h_left : h_right) + 1;
    }


template <typename T>
void Tree<T>::Rotate_right(Node_t* curr) noexcept // правый поворот вокруг curr
    {
    Node_t* tmp = curr -> left;
    tmp -> prev = curr -> prev;
    curr -> left = tmp -> right;
    if (curr -> left != nullptr)
        curr -> left -> prev = curr;
    tmp -> right = curr;
    if (curr -> prev == nullptr)
        root_ = tmp;
    else if (curr -> prev -> left == curr)
        curr -> prev -> left = tmp;
    else curr -> prev -> right = tmp;
    curr -> prev = tmp;
    Update_height(curr);
    Update_height(tmp);
    }


template <typename T>
void Tree<T>::Rotate_left(Node_t* curr) noexcept // левый поворот вокруг curr
    {
    Node_t* tmp = curr -> right;
    tmp -> prev = curr -> prev;
    curr -> right = tmp -> left;
    if (curr -> right != nullptr)
        curr -> right -> prev = curr;
    tmp -> left = curr;
    if (curr -> prev == nullptr)
        root_ = tmp;
    else if (curr -> prev -> left == curr)
        curr -> prev -> left = tmp;
    else curr -> prev -> right = tmp;
    curr -> prev = tmp;
    Update_height(curr);
    Update_height(tmp);
    }


template <typename T>
void Tree<T>::Rebalance(Node_t* curr) noexcept
    {
    while (curr != nullptr)
        {
        Update_height(curr);
        if (Balance_index(curr) == 2)
            {
            if (Balance_index(curr -> right) < 0)
                Rotate_right(curr -> right);
            Rotate_left(curr);
            }
        if (Balance_index(curr) == -2)
            {
            if (Balance_index(curr -> left) > 0)
                Rotate_left(curr -> left);
            Rotate_right(curr);
            }
        curr = curr -> prev;
        }
    }


template <typename T>
void Tree<T>::Height_update_lift(Node_t* curr) noexcept
    {
    Update_height(curr);
    while (curr -> prev != nullptr)
        {
        curr = curr -> prev;
        Update_height(curr);
        }
    }


template <typename T>
int Tree<T>::Count_height(Node_t* curr) const noexcept
    {
    if (curr != nullptr)
        return 0;
    int height_left = 0, height_right = 0;

    if (curr -> right != nullptr)
        {
        curr -> height++;
        height_right = Count_height(curr -> right);
        }
    else if (curr -> left != nullptr)
        {
        curr -> height++;
        height_left = Count_height(curr -> left);
        } 
    if (height_left > height_right)
        curr -> height = height_left + 1;    
    else curr -> height = height_right + 1;
    }


template <typename T>
void Tree<T>::Insert(T key)
    {
    if (root_ == nullptr)
        {
        root_ = new Node_t(key, nullptr);
        root_ -> left = nullptr;
        root_ -> right = nullptr;
        root_ -> height = 1;
        return;
        }
    Node_t* curr = Find_nearest_node(key);
    if (key > curr -> key)
        curr -> right = new Node_t(key, curr);
    else  if (key < curr -> key)
        curr -> left = new Node_t(key, curr);
    else 
        return;
    Rebalance(curr);
    }


template <typename T>
void Tree<T>::Erase(T key)
    {
    if (root_ == nullptr)
        {
        std::cout << "Tree is empty\n" << std::endl;
        return;
        }
    Node_t* curr = Find_elem(key);       
    if (curr == nullptr)
        return;
    else if (curr -> right != nullptr)
        Delete_if_right_is_not_empty(curr);
    else if (curr -> left != nullptr) 
        Delete_if_right_is_empty_but_left_not(curr);
    else if (curr -> prev != nullptr)
        {
        if (curr -> prev -> left == curr)
            curr -> prev -> left = nullptr;
        else curr -> prev -> right = nullptr;
        Rebalance(curr);
        delete curr;
        }
    else 
        {
        delete curr;
        root_ = nullptr;
        }
    }


template <typename T>
void Tree<T>::Delete_if_right_is_not_empty(Node_t* curr)
        {
        Node_t* min_node = Search_min(curr -> right);
        std::swap(curr -> key, min_node -> key);
        if (min_node == curr -> right)
            {
            if (curr -> right -> right != nullptr)
                curr -> right -> right -> prev = curr;
            curr -> right = curr -> right -> right;
            }
        else 
            {
            min_node -> prev -> left = min_node -> right;
            if (min_node -> right != nullptr)
                min_node -> right -> prev = min_node -> prev;
            else 
                min_node -> prev -> left = nullptr;
            }
        Rebalance(min_node);
        delete min_node;//right 
        }


template <typename T>
void Tree<T>::Delete_if_right_is_empty_but_left_not(Node_t* curr)
    {
    curr -> key = curr -> left -> key;
    if (curr -> left -> left != nullptr)
        curr -> left -> left -> prev = curr;
    if (curr -> left -> right != nullptr)
        curr -> left -> right -> prev = curr;
    curr -> right = curr -> left -> right;
    curr -> left = curr -> left -> left;
    Rebalance(curr);
    delete curr -> left;
    }


template <typename T>
void Tree<T>::Print_tree_to_graphiz() const
    {
    std::ofstream fout("graph.txt");
    fout << "digraph G{\n";
    Graphiz_translation(root_, fout);
    fout << "}";
    //To get png_file with image of the tree enter command using correct path to graph_visual.png "dot graph.txt -T png -o graph_visual.png"   
    }


template <typename T>
void Tree<T>::Graphiz_translation(Node_t* node, std::ofstream& fout) const 
            {
            if (node -> left)
                {
                fout << node -> key << " -> " << node -> left -> key << ";\n"; 
                Graphiz_translation(node -> left, fout);
                }

            if (node -> right)
                {
                fout << node -> key << " -> " << node -> right -> key << ";\n"; 
                Graphiz_translation(node -> right, fout);
                }
            }


template <typename T>
void Tree<T>::Print_tree(Node_t* node, std::ofstream& fout) const
            {
            if (node == 0)
                node = root_;
            fout << "{" << node -> key << "} "; 
            if (node -> left)
                fout << "left = {" << node -> left -> key << "} ";
            if (node -> right)
                fout << "left = {" << node -> right -> key << "} ";
            fout << std::endl;

            if (node -> left)
                {
                Print_tree(node -> left);
                }

            if (node -> right)
                {
                Print_tree(node -> right);
                }
            }


template <typename T>
int Tree<T>::K_least_element(int k) const noexcept
    {
    Node_t* curr = root_;
    if (curr == nullptr)
        {
        std::cout << "fault k > size of tree "; 
        return 0;
        }
    int counter = Under(curr -> left) + 1;

    while (true)
        {
        if (counter < k && curr -> right != nullptr)
            {
            curr = curr -> right;
            counter += 1 + Under(curr -> left);
            }
        else if (counter > k && curr -> left != nullptr)
            {
            curr = curr -> left;
            counter -= Under(curr) - Under(curr -> left);
            }
        else if (counter == k) 
            return curr -> key;
        else 
            {
            std::cout << "fault k > size of tree" << std::endl;
            return -1;
            }
        }
    }


template <typename T>
int Tree<T>::Numb_of_elem_less_than(int key) const noexcept
    {
    Node_t* curr = root_;
    int ret_value = 0;
    if (!curr)
        return 0;
    while (true)
        {
        if (key < curr -> key && curr -> left)
            curr = curr -> left;
        else if (key > curr -> key && curr -> right)
            curr = curr -> right;
        else break;
        }
    if (curr -> key < key)
        ret_value += Under(curr);
        
    else if (curr -> key == key)
        ret_value += Under(curr -> left);
        
    while (curr -> prev)
        {
        if (curr -> prev -> right == curr)
            ret_value += Under(curr -> prev -> left) + 1;
        curr = curr -> prev;
        }
    return ret_value;
    }


template <typename T>
typename Tree<T>::Node_t* Tree<T>::Search_min(Node_t* curr) const noexcept
            {
            while(curr -> left != nullptr)
                curr = curr -> left;
            return curr;
            }


template <typename T>
void Tree<T>::Clear() noexcept
    {
    while (root_ != nullptr)
        {
        if (root_ -> left != nullptr)
            root_ = root_ -> left;
        else if (root_ -> right != nullptr)  
            root_ = root_ -> right;
        else 
            {
            Node_t* tmp = root_ -> prev;
            if (tmp == nullptr)
                delete root_;
            else if (tmp -> left == root_)
                {
                tmp -> left = nullptr;
                delete root_;
                }
            else 
                {
                tmp -> right = nullptr;
                delete root_;
                }
            root_ = tmp;
            }
        }
    }


template <typename T>
typename Tree<T>::Node_t* Tree<T>::Find_nearest_node(T key) const noexcept
    {
    Node_t* curr = root_;
    while (root_)
        {
        if (key > curr -> key)
            if (curr -> right != nullptr)
                curr = curr -> right;
            else 
                return curr;
                
        else if (key < curr -> key)
            if (curr -> left != nullptr)
                curr = curr -> left;
            else 
                return curr;
        else 
            return curr;
        }
    return root_;
    }


template <typename T>
typename Tree<T>::Node_t* Tree<T>::Find_elem(T key) const noexcept
    {
    Node_t* curr = root_;
    while (curr)
        {
        if (key > curr -> key)
            curr = curr -> right;
        else if (key < curr -> key)
            curr = curr -> left;
        else return curr;
        }
    return curr;
    }
    