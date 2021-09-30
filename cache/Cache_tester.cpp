#include <cstdlib> //This program start tests for cache_2Q and ideal_cache
#include <string>
#include <ostream>
#include <sstream>
#include <iostream>
using namespace std;
int main(int argc, char** argv)
    {
    string program_name = argv[1];
    string command = program_name + " < ./Tests/";
    ostringstream stream;

    for (int i = 1; i < 12; i++)
        {
        stream << i;
        command += stream.str() + ".dat";
        system(command.c_str());
        command = program_name + " < ./Tests/";
        stream.str("");
        }
    
    }