#include "algorithm.h"

#include <map>
#include <iostream>
#include <ostream>
#include <vector>

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

        uint bad_pairs = 0; // this is how we check sr

        // The steps of the algorithm
        uint max_steps = (gpd->size()*gpd->size() - gpd->size()) / 2;
        for(int step = 2; step <= max_steps; ++step) {
            for(int i = 0; i < gpd->size(); ++i) {
                for(int j = 0; j < gpd->size(); ++j) {
                    /*if(bad_pairs == max_steps) {
                        return false;
                    }*/

                    if(i >= j) continue;

                    for(int k = 0; k < gpd->size(); ++k) {
                        auto x_k = gpd->get(i, k);
                        auto k_x = gpd->get(k, i);

                        auto y_k = gpd->get(j, k);
                        auto k_y = gpd->get(k, j);

                        if(((algo_tb->get(x_k, y_k) < step
                             && algo_tb->get(x_k, y_k) != 0)
                            || (algo_tb->get(y_k, x_k) < step
                                && algo_tb->get(y_k, x_k) != 0))
                            && algo_tb->get(i, j) == 0) {

                            algo_tb->set(i, j, step);
                            ++bad_pairs;
                        }

                        if(((algo_tb->get(k_x, k_y) < step
                             && algo_tb->get(k_x, k_y) != 0)
                            || (algo_tb->get(k_y, k_x) < step
                                && algo_tb->get(k_y, k_x) != 0))
                            && algo_tb->get(i, j) == 0) {

                            algo_tb->set(i, j, step);
                            ++bad_pairs;
                        }
                    }
                }
            }
        }

        return (bad_pairs != max_steps);
    }

    void sr_graph(GroupoidPtr gpd, std::ostream& out, bool rho) {
        auto to_vert = [] (int i, int j) -> std::string {
            if(i == j) {
                return "∆" + std::to_string(i);
            }
            if(i < j) {
                return std::to_string(i) + " " + std::to_string(j);
            } else {
                return std::to_string(j) + " " + std::to_string(i);
            }
        };

        out << "digraph G {"
                  << std::endl
                  << "\tedge [fontsize=10]"
                  << std::endl;

        if(out.good()) {
            for(int i = 0; i < gpd->size(); ++i) {
                for(int j = 0; j < gpd->size(); ++j) {
                    if(i >= j) continue;

                    std::map<std::string, std::string> edges;
                    for(int k = 0; k < gpd->size(); ++k) {
                        edges[to_vert(gpd->get(k, i), gpd->get(k, j))] += "λ<SUB>" + std::to_string(k) + "</SUB>, ";
                        if(rho) edges[to_vert(gpd->get(i, k), gpd->get(j, k))] += "ρ<SUB>" + std::to_string(k) + "</SUB>, ";
                    }

                    for (const auto& kv : edges) {
                        out << "\t\""
                            << to_vert(i, j)
                            << "\" -> \""
                            << kv.first
                            << "\" [label=<{"
                            << kv.second.substr(0, kv.second.length() - 2)
                            << "}>];"
                            << std::endl;
                    }
                }
            }
        }

        out << "}" << std::endl;
    }

} // end of namespace Algorithm