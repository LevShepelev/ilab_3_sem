#pragma once
#include <algorithm>
#include <iostream>
#include <unistd.h>
#include <sys/types.h> 
#include <iostream>
#include <fstream>

template <typename T>
class Tree final
    {
    struct Node_t
        {
        Node_t(T key, Node_t* prev) : key(key), left(nullptr), right(nullptr), prev(prev), height(1), under(0) {}
        T key;
        Node_t* left;
        Node_t* right;
        Node_t* prev;
        int height;
        int under; // under shows us, how many nodes under this node
        Node_t(Node_t* node) : key(node -> key), left(nullptr), right(nullptr), prev(nullptr), height(node -> height), under(node -> under) {}
        };
    

    public:
        Tree() : root_(nullptr) {}
        Tree(const Tree& tr);
        Tree(Tree&& tr);
        Tree& operator= (const Tree& tr);
        Tree& operator= (Tree&& tr);
        ~Tree();

        void Insert(T key);
        void Erase(T key);
        void Print_tree_to_graphiz();
        void Print_tree(Node_t* node);
        void Graphiz_translation(Node_t* node, FILE* fout);
        int K_least_element(int k);
        int Numb_of_elem_less_than(int key);

    private: 
        Node_t* root_;

        int  Height(Node_t* curr) { return curr ? curr -> height : 0; }
        int  Under(Node_t* curr)  { return curr ? curr -> under + 1 : 0; }
        int  Balance_index(Node_t* curr) { return Height(curr -> right) - Height(curr -> left); }
        void Update_height(Node_t* curr);
        void Rotate_right(Node_t* curr);
        void Rotate_left(Node_t* curr);
        void Height_update_lift(Node_t* curr);
        void Rebalance(Node_t* curr);
        int  Count_height(Node_t* curr);
        Node_t* Search_min(Node_t* curr);
        void Clear();
        Node_t* Find_nearest_node(T key);
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
Tree<T>::Tree(Tree&& tr) 
    {
    std::swap(tr.root_, root_);
    }


template <typename T>
Tree<T>& Tree<T>::operator= (const Tree& tr)
    {
    if (this == &tr)
        return *this;
        
    Tree* tmp = new Tree();
    tmp -> root_ = root_;
    delete tmp;
    tmp = new Tree(tr);
    root_ = tmp -> root_;
    return *this;
    } 


template <typename T>
Tree<T>& Tree<T>::operator= (Tree&& tr)
    {
    if (this == &tr)
        return *this;
    std::swap(root_, tr.root_);
    return *this;
    }


template <typename T>
void Tree<T>::Update_height(Node_t* curr)
    {
    int h_left =  Height(curr -> left);
    int h_right = Height(curr -> right);
    curr -> under  = Under(curr -> left) + Under(curr -> right);
    curr -> height = (h_left > h_right ? h_left : h_right) + 1;
    }


template <typename T>
void Tree<T>::Rotate_right(Node_t* curr) // правый поворот вокруг curr
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
void Tree<T>::Rotate_left(Node_t* curr) // левый поворот вокруг curr
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
void Tree<T>::Rebalance(Node_t* curr)
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
void Tree<T>::Height_update_lift(Node_t* curr)
    {
    Update_height(curr);
    while (curr -> prev != nullptr)
        {
        curr = curr -> prev;
        Update_height(curr);
        }
    }


template <typename T>
int Tree<T>::Count_height(Node_t* curr)
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
    Node_t* curr = root_;
    while (curr)
        {
        if (key > curr -> key)
            curr = curr -> right;
        else if (key < curr -> key)
            curr = curr -> left;
        else  
            {
            Node_t* min_node;
            if (curr -> right != nullptr)
                {
                min_node = Search_min(curr -> right);
                
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
            else if (curr -> left != nullptr) 
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
            else if (curr -> prev != nullptr)
                {
                if (curr -> prev -> left == curr)
                    curr -> prev -> left = nullptr;
                else curr -> prev -> right = nullptr;
                Rebalance(curr);
                delete curr;
                }
            else 
                delete curr;
                
            return;
            }
        }

    }


template <typename T>
void Tree<T>::Print_tree_to_graphiz()
    {
    FILE* fout = fopen("graph.txt", "w+");
    fprintf(fout, "digraph G{\n");
    Graphiz_translation(root_, fout);
    fprintf(fout, "}");
    fclose(fout);
    int fork_code = fork();
    if (fork_code == 0)
        {
        system("dot graph.txt -T png -o graph_visual.png");
        exit(0);
        }   
    }


template <typename T>
void Tree<T>::Graphiz_translation(Node_t* node, FILE* fout)
            {
            if (node -> left)
                {
                fprintf(fout, "%d -> %d;\n", node -> key, node -> left -> key);
                Graphiz_translation(node -> left, fout);
                }

            if (node -> right)
                {
                fprintf(fout, "%d -> %d;\n", node -> key, node -> right -> key);
                Graphiz_translation(node -> right, fout);
                }
            }


template <typename T>
void Tree<T>::Print_tree(Node_t* node)
            {
            if (node == 0)
                node = root_;
            printf("{%d} ", node -> key);
            if (node -> left)
                printf("left = {%d} ",  node -> left -> key);
            if (node -> right)
                printf("right = {%d} ", node -> right -> key);
            printf("\n");
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
int Tree<T>::K_least_element(int k)
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
int Tree<T>::Numb_of_elem_less_than(int key)
    {
    Node_t* curr = root_;
    int ret_value = 0;
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
typename Tree<T>::Node_t* Tree<T>::Search_min(Node_t* curr)
            {
            while(curr -> left != nullptr)
                curr = curr -> left;
            return curr;
            }


template <typename T>
void Tree<T>::Clear()
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
typename Tree<T>::Node_t* Tree<T>::Find_nearest_node(T key)
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