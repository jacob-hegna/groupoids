#include <iostream>

#include "algorithm.h"
#include "groupoid.h"

bool test_lorries_rnd_gpd() {
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

    Algorithm::check_sr(groupoid, algo_tb);

    return *algo_tb == *expect_tb;
}

int main(int argc, char* argv[]) {
    // make sure everything still works
    if(!test_lorries_rnd_gpd()) {
        std::cout << "[TEST FAILURE] [Lorrie's random groupoid]" << std::endl;
        std::cout << "The random groupoid below might not be analyzed correctly!" << std::endl;
    }

    // spit out a random groupoid with its table
    auto groupoid = Groupoid::from_random(5);
    auto algo_tb  = std::make_shared<Groupoid>(5);

    Algorithm::check_sr(groupoid, algo_tb);

    std::cout << "Groupoid: "
              << std::endl
              << groupoid->to_str()
              << std::endl
              << "----------"
              << std::endl
              << algo_tb->to_str()
              << std::endl;
}