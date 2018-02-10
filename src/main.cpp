#include <cstring>
#include <iostream>
#include <unistd.h>
#include <thread>

#include "algorithm.h"
#include "groupoid.h"
#include "test.h"
#include "parser.h"

int main(int argc, char* argv[]) {
    // default values
    uint size            = 4;
    uint iterations      = 1;
    bool help_shown      = false;
    auto help_short      = "Usage: " + std::string(argv[0]) + " [-hn:i:] [test|generate-random|generate-sr|nsr-graph]";
    auto help_long       = std::string("\t-h print this message\n")
                         + std::string("\t-n size of the groupoids to consider\n")
                         + std::string("\t-i number of iterations to run (if 0, continue indefinitely)\n");

    char c;
    while((c = getopt(argc, argv, "hvn:i:t:o:")) != -1) {
        switch(c) {
            case 'h':
                help_shown = true;
                std::cout << help_short << std::endl
                          << help_long  << std::endl;
                break;
            case 'n':
                size       = atoi(optarg);
                break;
            case 'i':
                iterations = atoi(optarg);
                break;
        }
    }

    if(optind >= argc && !help_shown) {
        std::cout << help_short << std::endl;
        return 1;
    }

    // I'm mixing up my curly brace style here, but otherwise this is unreadable
    if(strcmp(argv[optind], "test") == 0)
    {
        Test::run_all_tests();
    }
    else if(strcmp(argv[optind], "generate-random") == 0)
    {
        for(int i = 0; i < iterations; ++i) {
            auto groupoid = Groupoid::from_random(size);
            std::cout << groupoid->to_str() << std::endl;

            if(i != iterations - 1) {
                std::cout << std::endl;
            }
        }
    }
    else if(strcmp(argv[optind], "generate-sr") == 0)
    {
        int i = 0;
        while(i < iterations) {
            auto groupoid = Groupoid::from_random(size);
            if(Algorithm::check_sr(groupoid)) {
                std::cout << groupoid->to_str() << std::endl;
                ++i;

                if(i != iterations) {
                    std::cout << std::endl;
                }
            }
        }
    }
    else if(strcmp(argv[optind], "nsr-graph") == 0)
    {
        auto gpd = parse_groupoid(std::cin);
        Algorithm::sr_graph(gpd, std::cout, true);
    }
}