#include <stdio.h>
#include <atomic>
#include <thread>
#include <vector>
#include <iostream>

#include "mingw.thread.h"

//Include specific logger headers
#include"logger.h"


// using namespace std;
using namespace std::chrono;

//Use this macro to switch on multi-threading mode
//#define MULTI_THREAD


int main(int argc, char* argv[])
{
   InitLoggerImpl( "E://myLog.log", eLogLevel::llDEBUG );

    unsigned int thread_count = 4;
    unsigned int howmany      = 100000; //1000000;
    std::vector<std::thread> threads;
    auto start = system_clock::now();


#if !defined(MULTI_THREAD)
    for(unsigned int i=0; i < howmany; i++)
    {
        //Has to be customized for every logger
       //CPP_INFO( " Message + all required information, #" );
       CPP_INFO( " Message + all required information, #" << i );
        // C_INFO( "Message + all required information, # %d", i );
    }
#else
    howmany /= thread_count;
    for (int t = 0; t < thread_count; ++t)
    {
        threads.push_back(std::thread([&]
        {
            for(unsigned int i=0; i < howmany; i++)
            {
                //Has to be customized for every logger
                LOG(INFO) << " Message + all required information, #" << i;
            }
        }));
    }


    for(auto &t:threads)
    {
        t.join();
    };

    howmany *= thread_count;

#endif

    auto delta = system_clock::now() - start;
    auto delta_d = duration_cast<duration<double>> (delta).count();

    // CPP_INFO( "Time = " << (double)howmany / delta_d << " per second, total time = "  << delta_d );
    std::cout << "Time = " << (double)howmany / delta_d << " per second, total time = "  << delta_d << std::endl;
    //Logger uninitialization if necessary

    return 0;
}