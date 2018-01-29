#include <iostream>
#include <unistd.h>
#include <thread>

#include "algorithm.h"
#include "groupoid.h"
#include "test.h"

void search_nsr(uint size, uint iterations, bool verbose) {
    uint separating = 0;
    uint i = 0;
    while(i < iterations || iterations == 0) {
        auto groupoid = Groupoid::from_random(size);
        auto algo_tb  = std::make_shared<Groupoid>(size);
        bool nsr = Algorithm::check_sr(groupoid, algo_tb);
        
        if(nsr) {
            ++separating;

            std::cout << "(" << separating << "/" << i << ") - "
                      << (double)separating/(double)i << "%"
                      << std::endl;

            std::cout << groupoid->to_str() << std::endl;

            if(verbose) {
                std::cout << std::endl << algo_tb->to_str() << std::endl;
            }

            std::cout << std::endl;
        }

        ++i;
    }
}

int main(int argc, char* argv[]) {
    // default values
    uint size       = 4;
    uint iterations = 1000;
    uint threads    = 1;
    bool verbose    = false;
    bool help_shown = false;
    auto help_short = "Usage: " + std::string(argv[0]) + " [-hvn:i:t:] [test|random|nsr]";
    auto help_long  = std::string("\t-h print this message\n")
                    + std::string("\t-v verbose, show algorithm details\n")
                    + std::string("\t-n size of the groupoids to consider\n")
                    + std::string("\t-i number of iterations to run (if 0, continue indefinitely)")
                    + std::string("\t-t threads to use");

    char c;
    while((c = getopt(argc, argv, "hvn:i:t:")) != -1) {
        switch(c) {
            case 'h':
                help_shown = true;
                std::cout << help_short << std::endl
                          << help_long  << std::endl;
                break;
            case 'v':
                verbose = true;
                break;
            case 'n':
                size       = atoi(optarg);
                break;
            case 'i':
                iterations = atoi(optarg);
                break;
            case 't':
                threads    = atoi(optarg);
                break;
        }
    }

    // this might be the problem
    if(optind >= argc && !help_shown) {
        std::cout << help_short << std::endl;
        return 1;
    }

    if(strcmp(argv[optind], "test") == 0) {
        std::cout << "[test] [Lorrie's random groupoid] ";
        if(!Test::lorries_rnd_gpd()) {
            std::cout << "[FAILURE]" << std::endl;
        } else {
            std::cout << "[PASS]" << std::endl;
        }

        std::cout << "[test] [Z5] ";
        if(!Test::lorries_rnd_gpd()) {
            std::cout << "[FAILURE]" << std::endl;
        } else {
            std::cout << "[PASS]" << std::endl;
        }
    } else if(strcmp(argv[optind], "random") == 0) {
        auto groupoid = Groupoid::from_random(size);
        auto algo_tb  = std::make_shared<Groupoid>(size);

        Algorithm::check_sr(groupoid, algo_tb);

        std::cout << groupoid->to_str() << std::endl
                  << std::endl
                  << algo_tb->to_str()  << std::endl;
    } else if(strcmp(argv[optind], "nsr") == 0) {
        std::vector<std::thread> thread_pool;
        for(int i = 0; i < threads; ++i) {
            thread_pool.emplace_back(&search_nsr, size, iterations, verbose);
        }
        for(auto& thread : thread_pool) {
            thread.join();
        }
    }
}