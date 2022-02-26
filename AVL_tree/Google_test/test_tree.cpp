#include <gtest/gtest.h>
#include <iostream>
#include "../includes/AVL_tree.h"

TEST(AVL_tree, Insert_Erase) {
    Tree<int> tree;
    const int count = 10;
    for (int i = 0; i < count; ++i)
        {
        ASSERT_EQ(tree.Get_size(), i);
        tree.Insert(i);
        }
    for (int i = 0; i < count; ++i)
        {
        tree.Erase(i);
        ASSERT_EQ(tree.Get_size(), count - i - 1);
        }
}
TEST(AVL_tree, Destuctor){
    const int count = 10;
    Tree<int>* tree = new Tree<int>();
    for (int i = 0; i < count; ++i)
        tree -> Insert(i);
    delete tree;       
}

TEST(AVL_tree, Copy_constuctor) {
    const int count = 10;
    Tree<int>* tree = new Tree<int>();
    for (int i = 0; i < count; ++i)
        tree -> Insert(i);
    Tree<int> tree_copy(*tree);
    ASSERT_EQ(tree_copy.Get_size(), count);
    delete tree;
    ASSERT_EQ(tree_copy.Get_size(), count);
}

TEST(AVL_tree, Move_consructor) {
    const int count = 10;
    Tree<int>* tree = new Tree<int>();
    for (int i = 0; i < count; ++i)
        tree -> Insert(i);
    
    Tree<int>* tree_copy = new Tree<int>(Tree<int>(*tree));
    ASSERT_EQ(tree_copy -> Get_size(), count);
    delete tree;
    ASSERT_EQ(tree_copy -> Get_size(), count);
    delete tree_copy;
}

TEST(AVL_tree, Copy_assigment) {
    const int count = 10;
    Tree<int>* tree = new Tree<int>();
    for (int i = 0; i < count; ++i)
        tree -> Insert(i);
    Tree<int> tree_copy = *tree;
    ASSERT_EQ(tree_copy.Get_size(), count);
    delete tree;
    ASSERT_EQ(tree_copy.Get_size(), count);
}

TEST(AVL_tree, Move_assigment) {
    const int count = 10;
    Tree<int>* tree = new Tree<int>();
    for (int i = 0; i < count; ++i)
        tree -> Insert(i);
    Tree<int> tree_copy = Tree<int>(*tree);
    int size = tree_copy.Get_size();
    ASSERT_EQ(size, count);
    delete tree;
    ASSERT_EQ(tree_copy.Get_size(), count);
}



int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}