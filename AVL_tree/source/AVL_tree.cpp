#include "../include/AVL_tree.h"

int main()
    {
    Tree<int> tr;
    char symb = 0;
    int elem = 0;
        
    while (symb != '\n' || symb != std::cin.eof())
        {
        scanf("%c", &symb);
        if (symb == '\n')
            break;
        scanf("%d", &elem);
        if (symb == 'k')
            tr.Insert(elem);

        else if (symb == 'm')
            std::cout << tr.K_least_element(elem) << " ";
        
        else if (symb == 'n')
            std::cout << tr.Numb_of_elem_less_than(elem) << " ";
        }
    std::cout << std::endl;
    #ifdef GRAPH
        tr.Print_tree_to_graphiz();
    #endif
    }