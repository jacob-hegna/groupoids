#include "test.h"

#include "algorithm.h"
#include "groupoid.h"

#include <iostream>
#include <vector>

namespace Test {
    bool run_all_tests() {
        bool success = true;

        std::cout << "[test] [Lorrie's random groupoid] ";
        if(!(success &= Test::lorries_rnd_gpd())) {
            std::cout << "[FAILURE]" << std::endl;
        } else {
            std::cout << "[PASS]" << std::endl;
        }

        std::cout << "[test] [Z5] ";
        if(!(success &= Test::lorries_rnd_gpd())) {
            std::cout << "[FAILURE]" << std::endl;
        } else {
            std::cout << "[PASS]" << std::endl;
        }

        return success;
    }

    bool lorries_rnd_gpd() {
        std::vector<std::vector<uint>> lorries_table = {{
            {3, 4, 1, 0, 4},
            {2, 3, 0, 1, 2},
            {0, 2, 4, 3, 1},
            {1, 0, 3, 4, 1},
            {1, 1, 0, 3, 2}
        }};

        std::vector<std::vector<uint>> lorries_table_algo = {{
            {1, 2, 3, 3, 2},
            {0, 1, 3, 3, 2},
            {0, 0, 1, 2, 2},
            {0, 0, 0, 1, 2},
            {0, 0, 0, 0, 1}
        }};

        auto groupoid  = std::make_shared<Groupoid>(lorries_table);
        auto expect_tb = std::make_shared<Groupoid>(lorries_table_algo);
        auto algo_tb   = std::make_shared<Groupoid>(groupoid->size());

        auto sr = Algorithm::check_sr(groupoid, algo_tb);

        return (*algo_tb == *expect_tb) && !sr;
    }

    bool Z5() {
        std::vector<std::vector<uint>> Z5_table = {{
            {0, 1, 2, 3, 4},
            {1, 2, 3, 4, 0},
            {2, 3, 4, 0, 1},
            {3, 4, 0, 1, 2},
            {4, 0, 1, 2, 3}
        }};

        std::vector<std::vector<uint>> Z5_table_algo = {{
            {1, 0, 0, 0, 0},
            {0, 1, 0, 0, 0},
            {0, 0, 1, 0, 0},
            {0, 0, 0, 1, 0},
            {0, 0, 0, 0, 1}
        }};

        auto groupoid  = std::make_shared<Groupoid>(Z5_table);
        auto expect_tb = std::make_shared<Groupoid>(Z5_table_algo);
        auto algo_tb   = std::make_shared<Groupoid>(groupoid->size());

        auto sr = Algorithm::check_sr(groupoid, algo_tb);

        return (*algo_tb == *expect_tb) && sr;
    }
}