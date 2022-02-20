#include "../include/AVL_tree.h"

int main()
    {
    Tree<int> tr;
    char symb = 0;
    int elem = 0;
    char s[30] = "./Tests/test005";
    std::ifstream in(s);
    if (!in.is_open())
        {
        std::cout << "No such file " << '"' <<s << '"' << std::endl;
        return -1;
        }
        
    while (true)
        {
        in >> symb;
        if (symb == 'q' || std::cin.eof())
            break;
        in >> elem;
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