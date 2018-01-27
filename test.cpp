#include "test.h"

#include "algorithm.h"
#include "groupoid.h"

#include <vector>

namespace Test {
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