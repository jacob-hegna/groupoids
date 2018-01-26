#include "algorithm.h"

namespace Algorithm {

    // Clean this mess up
    bool check_sr(GroupoidPtr gpd, GroupoidPtr algo_tb) {
        if(!gpd) {
            return false;
        }

        if(!algo_tb) {
            algo_tb = std::make_shared<Groupoid>(gpd->size());
        }

        // step 1: the diagonal pairs
        for(int i = 0; i < gpd->size(); ++i) {
            algo_tb->set(i, i, 1);
        }

        // The steps of the algorithm
        for(int step = 2; step <= 3; ++step) {
            for(int i = 0; i < gpd->size(); ++i) {
                for(int j = 0; j < gpd->size(); ++j) {
                    if(i >= j) continue;

                    for(int k = 0; k < gpd->size(); ++k) {
                        auto x_k = gpd->get(i, k);
                        auto k_x = gpd->get(k, i);

                        auto y_k = gpd->get(j, k);
                        auto k_y = gpd->get(k, j);

                        if((algo_tb->get(x_k, y_k) == step-1
                            || algo_tb->get(y_k, x_k) == step-1)
                            && algo_tb->get(i, j) == 0) {

                            algo_tb->set(i, j, step);
                        }

                        if((algo_tb->get(k_x, k_y) == step-1
                            || algo_tb->get(k_y, k_x) == step-1)
                            && algo_tb->get(i, j) == 0) {

                            algo_tb->set(i, j, step);
                        }
                    }
                }
            }
        }

        return true;
    }

} // end of namespace Algorithm