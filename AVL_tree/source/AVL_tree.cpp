#include "../includes/AVL_tree.h"

int main()
    {
    Tree<int> tr;
    char symb = 0;
    int elem = 0;

    std::cin.get(symb);
    while (symb != '\n' || symb != std::cin.eof())
        {
        std::cin >> elem;
        if (symb == 'k')
            tr.Insert(elem);

        else if (symb == 'm')
            std::cout << tr.K_least_element(elem) << " ";
        
        else if (symb == 'n')
            std::cout << tr.Numb_of_elem_less_than(elem) << " ";

        std::cin.get(symb);
        if (symb == '\n' || !std::cin)
            break;

        std::cin.get(symb);
        if (symb == '\n' || !std::cin)
            break;
        }
    std::cout << std::endl;
    #ifdef GRAPH
        tr.Print_tree_to_graphiz();
    #endif
    }