#include "cache.h"

int main()
    {
    clock_t start, end;
    start = clock();
    int total_memory = 0, numb_of_pages = 0, page_number = 0;

    cin >> total_memory >> numb_of_pages;
    Cache<char> cache((total_memory + 3) / 4, total_memory / 2, (total_memory + 1) / 4);
    for (int i = 0; i < numb_of_pages; i++)
        {
        cin >> page_number;
        cache.Searching(page_number);
        }
    end = clock();
    //detailed output
    //printf("Hits = %7ld, hit_procent = %5f, time = %10f\n", cache.hit_counter_, (float) cache.hit_counter_ / numb_of_pages * 100, (float) (end - start) / (CLOCKS_PER_SEC)); 
    cout << cache.hit_counter_ << endl;
    }