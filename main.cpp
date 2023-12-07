#include <iostream>
#include "threadpool1.h"

void printX()
{
    for(int i=0;i<1000;++i)
        std::cout<<i<<" ";
}
void printZ()
{
    std::cout<<"hello ";
}


int main() {
    std::cout<<"main thread begin runing!"<<std::endl;
    thread_pool threadpool;
    threadpool.submit(printX);
    threadpool.submit(printX);
    threadpool.submit(printZ);

    return 0;
}
