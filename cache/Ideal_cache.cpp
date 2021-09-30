#include "Ideal_cache.h"

int main()
    {
    clock_t start, end;
    start = clock();
    int total_memory = 0, numb_of_pages = 0, page_number = 0;
    cin >> total_memory >> numb_of_pages;
    int requests[numb_of_pages];
    Ideal_cache<char> cache(total_memory);

    for (int i = 0; i < numb_of_pages; i++)
        {
        cin >> page_number;
        requests[i] = page_number;
        cache.Reading_pages(page_number, i);
        }

    for (int i = 0; i < numb_of_pages; i++)
        {
        cache.Searching(requests[i], i);
        }
    end = clock();
    //detailed output
    //printf("Hits = %7d, hit_procent = %5f, time = %8f\n", cache.hit_counter_, (float) cache.hit_counter_ / numb_of_pages * 100, (float) (end - start) / (CLOCKS_PER_SEC));
    cout << cache.hit_counter_ << endl;
    }