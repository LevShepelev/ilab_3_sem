#include "../include/Biton_Sort.hpp"
#define COMPARE_CPU

// run "./Biton_Sort 1000" where 1000 - size of array

int main(int, char* argv[]) try {
    std::chrono::high_resolution_clock::time_point TimeStart, TimeFin;\
    double Dur;
    OclApp app;
    int size = atoi(argv[1]);
    cl::vector<TYPE> array(size);
    srand(time(NULL));
    for (int i = 0; i < size; i++) 
        array[i] = rand() % 10000000;
    
    cl::vector<TYPE> array_copy(array);

    TimeStart = std::chrono::high_resolution_clock::now();
    cl::Event Evt = app.Bitonic_sort(array, size);
    TimeFin = std::chrono::high_resolution_clock::now();
    Dur = std::chrono::duration_cast<std::chrono::milliseconds>(TimeFin - TimeStart).count();
    std::cout << "GPU time measured: " << Dur << " ms" << std::endl;

    #ifdef COMPARE_CPU
      TimeStart = std::chrono::high_resolution_clock::now();
      std::sort(array_copy.begin(), array_copy.end());
      TimeFin = std::chrono::high_resolution_clock::now();
      Dur = std::chrono::duration_cast<std::chrono::milliseconds>(TimeFin - TimeStart).count();
      std::cout << "CPU time measured: " << Dur << " ms" << std::endl;
    #endif

    } catch (cl::Error &err) {
        std::cerr << "OCL ERROR " << err.err() << ":" << err.what() << std::endl;
        return -1;
    } catch (std::runtime_error &err) {
        std::cerr << "RUNTIME ERROR " << err.what() << std::endl;
        return -1;
    } catch (...) {
        std::cerr << "UNKNOWN ERROR\n";
        return -1;
}