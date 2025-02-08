#include <iostream>
#include <omp.h>

int main() {
#pragma omp parallel
    {
        std::cout << "thread " << omp_get_thread_num() << std::endl;
    }
    return 0;
}